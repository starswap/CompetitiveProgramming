for i in $(seq 7 1 100)
do
    echo $i
    python G.gen.py > "G.in$i.txt"
    diff --suppress-common-lines -y <(cat "G.in$i.txt" | python G.brute.py) <(cat "G.in$i.txt" | ./a.exe)
done

