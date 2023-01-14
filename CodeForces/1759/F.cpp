#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d",&T);
    for (int t=0;t<T;++t) {
        int N,P;
        scanf("%d %d",&N,&P);
        vector<int> inputDigits(N);
        
        for (int n=0; n < N; ++n) {
            scanf("%d",&inputDigits[n]);
        }

        int z = *inputDigits.rbegin();

        set<int> digitSet(inputDigits.begin(),inputDigits.end());


        // Find longest 0...a run amongst present digits
 
        int zeroTo = -1;
        for (int digit : digitSet) {
            if (digit > zeroTo + 1) break;
            zeroTo = digit;
        }

        // Find longest b .. p run amongst present digits
        int kToEnd = P;
        for (auto digIT = digitSet.rbegin(); digIT != digitSet.rend(); digIT++) {
            if (*digIT < kToEnd - 1) break;
            kToEnd = *digIT;
        }

        int ans = -1;

        if (zeroTo >= z) {
            ans = max(0,kToEnd-1-z);
        }
        else {
            ans = P - 1 - z; // have to go all the way round,
            ans += 1;        // and tick over back to the beginning


            // tick over to the beginning
            digitSet.insert(0);
            int carry = 1;
            for (int i=N-2;i>-1;i--) {
                int newDigit = (inputDigits[i] + carry) % P;
                digitSet.insert(newDigit);
                carry = (inputDigits[i] + carry) / P;
            } 

            if (carry > 0)
                digitSet.insert(carry);
            
            // Find longest run a .. z where z is the final digit of the original number
            int longestEndingInZ = z;
            auto it = digitSet.find(z);
            while (it != digitSet.begin() && *it == longestEndingInZ) {
                it--;
                longestEndingInZ--;   
            }
            longestEndingInZ++;

            // find new longest run from 0 to as far as we can get.
            for (int digit : digitSet) {
                if (digit > zeroTo + 1) break;
                zeroTo = digit;
            }

            if (zeroTo < longestEndingInZ - 1) {
                ans += longestEndingInZ - 1;

            }
            else {} // we're done
        }
        cout << ans << endl;
    }
    return 0;
}

// let z be the final digit of the input number 
// make a set of all the input digits
// Find a giving longest 0 .. a run amongst present digits
// Find b giving longest b .. p-1 run amongst present digits
// if we can get from zero to z (as determined by a >= z)
//     the answer is the distance from z to b - 1 (or 0 if this is negative)
// otherwise:
//     we need to take z all the way to the end and back around
//     compute the new number once we roll over the final digit and add all of the digits of the new number to the digit set
//     (ex: if the original number is (1 2 9 9 4) the new number is (1 3 0 0 0) and the digit set is now (0 1 2 3 4 9 9)  
//     Now, we do almost the same thing
//     find c giving the longest 0 .. c run amongst digits in the set
//     find d giving the longest d .. z run amongst digits in the set
//     if (c >= d - 1) we can get from 0 to at least d now. We know we have from d .. z and we already got from z .. p - 1 on rolling over
//          ans = P - 1 - z // (cost of getting the final digit to maximum)
//                + 1;        // to roll over
//     otherwise:
//          we have z .. p - 1 from before. We also have 0 .. c and d .. z. 
//          So we need c .. d.
//          We can only get this by adding 1 to the number until we reach d. 
//          The last digit of the number is currently 0.
//          therefore:
//          ans = P - 1 - z  // (cost of getting the final digit to maximum)
//                + 1        // to roll over
//                + d - 1    // to get to d.
// print(ans)


