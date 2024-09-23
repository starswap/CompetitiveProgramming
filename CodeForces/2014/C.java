import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.lang.Math;

public class Main {
    private static final long INF = 1_000_000_000_000_000L;

    public static boolean robin_comes(long x, List<Long> wealths) {
        long total_wealth = wealths.stream().reduce(0L, Long::sum) + x;
        int unhappy = 0;
        long maxi = 0;
        for (long w : wealths) {maxi = Math.max(maxi, w);}

        boolean done = false;
        for (long w : wealths) {
            if (w == maxi && !done) {done = true; continue;};
            if (w * (2 * wealths.size()) < total_wealth) {
                unhappy++;
            }
        }
        return (unhappy * 2 > wealths.size());
    }


    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int T = in.nextInt();
        for (int t = 0; t < T; ++t) {
            int N = in.nextInt();
            ArrayList<Long> list = new ArrayList<>(N);

            for (int n = 0; n < N; ++n) {
                list.add(n, in.nextLong());
            }

            long lo = -1; // out
            long hi = INF; // in
            while (hi - lo > 1) {
                long mi = (hi + lo) / 2;
                if (robin_comes(mi, list)) {
                    hi = mi;
                } else {
                    lo = mi;
                }
            }
            if (lo == INF - 1) {
                System.out.println("-1");
            } else {
                System.out.println(hi);
            }
        }
    }
}