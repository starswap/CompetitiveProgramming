import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Scanner;
import java.util.TreeSet;

public class D {

  record Pair<A extends Comparable<A>, B extends Comparable<B>>(A first, B second) implements
      Comparable<Pair<A, B>> {

    @Override
    public int compareTo(Pair<A, B> o) {
      if (this.first == o.first) {
        return this.second.compareTo(o.second);
      } else {
        return this.first.compareTo(o.first);
      }
    }
  }

  private static List<Integer> solve(List<Integer> nums) {
    TreeSet<Pair<Integer, Integer>> badPairs = new TreeSet<>();
    TreeSet<Integer> numsRemaining = new TreeSet<>();
    List<Integer> deleted = new ArrayList<>();
    for (int i = 0; i < nums.size() - 1; ++i) {
      if (gcd(nums.get(i), nums.get(i + 1)) == 1) {
        badPairs.add(new Pair<>(i, i + 1));
      }
      numsRemaining.add(i);
    }
    numsRemaining.add(nums.size() - 1);
    if (gcd(nums.get(0), nums.get(nums.size() - 1)) == 1) {
      badPairs.add(new Pair<>(nums.size() - 1, 0));
    }

    while (!badPairs.isEmpty()) {
      Iterator<Pair<Integer, Integer>> it = badPairs.iterator();
      List<Pair<Integer, Integer>> toAdd = new ArrayList<>();
      while (it.hasNext()) {
        Pair<Integer, Integer> p = it.next();
        if (numsRemaining.contains(p.first())) {
          deleted.add(p.second());
          numsRemaining.remove(p.second());
          if (numsRemaining.size() > 0) {
            int nextId;
            if (numsRemaining.higher(p.second()) == null) {
              nextId = numsRemaining.first();
            } else {
              nextId = numsRemaining.higher(p.second());
            }
            if (gcd(nums.get(p.first()), nums.get(nextId)) == 1) {
              // System.out.println(new Pair<>(p.first(), nextId));
              toAdd.add(new Pair<>(p.first(), nextId));
            }
          }
        }
        it.remove();
      }
      for (Pair<Integer, Integer> p : toAdd) {
        badPairs.add(p);
      }
    }

    return deleted;
  }

  private static int gcd(int x, int y) {
    if (y == 0) {
      return x;
    } else {
      return gcd(y, x % y);
    }
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int T = sc.nextInt();

    for (int t = 0; t < T; ++t) {
      int N = sc.nextInt();
      List<Integer> nums = new ArrayList<>(N);
      for (int i = 0; i < N; ++i) {
        nums.add(sc.nextInt());
      }
      List<Integer> deleted = solve(nums);
      System.out.print(deleted.size());
      for (int d : deleted) {
        System.out.print(' ');
        System.out.print(d + 1);
      }
      System.out.print('\n');
    }
  }


}
