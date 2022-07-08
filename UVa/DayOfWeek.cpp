#include <bits/stdc++.h>
using namespace std;

const vector<string> days = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

int daysToLast(int day, int month, int year) {
	vector<int> daysOfMonth = {31,28,31,30,31,30,31,31,30,31,30,31};
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0 ) {
		daysOfMonth[1] = 29;
	}
	
	int dd = daysOfMonth[month-1] - day;
	for (;month<12;month++)
		dd += daysOfMonth[month];
	return dd;
}

int main() {
	int day = 29; int month = 5; int year = 2013;
	
	cin >> day; cin >> month; cin >> year;
	
	int rDay = 26; int rMonth = 6; int rYear = 2022; int refDoW = 6;
	

	
	cout << daysToLast(day,month,year) << endl;
	cout << daysToLast(rDay,rMonth,rYear) << endl;
	
	int dDay = daysToLast(rDay,rMonth,rYear) - daysToLast(day,month,year);
	
	//int multfact = -1;
	//if (year > rYear) {
		// int temp = rYear;
	//	rYear = year; year = temp;
//	}

	int numFours = floor(year/4) - floor(rYear/4);
	int numHundreds = floor(year/100) - floor(rYear/100);
	int numFourHundreds = floor(year/400) - floor(rYear/400);
	int numYears = year - rYear;
	
	cout << numYears << endl;
	cout << numHundreds << endl;
	cout << numFourHundreds << endl;
	cout << numFours << endl;
	
	dDay += numYears * 365;
	dDay += numFours - numHundreds + numFourHundreds;
	

	cout << dDay << endl;
	int index = ((refDoW + dDay) % 7);
	if (index < 0)
		index += 7;
	cout << index << endl; 
	cout << days[index] << endl;
	
	
	return 0;
}