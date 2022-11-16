import kotlin.math.max

fun swap(side: Char):Char =
    when (side) {
        'L' -> 'R'
        else -> 'L'
    }

fun main() {
    val (n,k) = readln().split(" ").map(String::toInt);
    val path  = readln();

    var fallingKids = 0;
    var curr = 'L';
    for (i in 0 until n) {
        if (path[i] != curr) fallingKids++;
        else curr = swap(curr);
    }

    println(max(k - fallingKids,0));
}
