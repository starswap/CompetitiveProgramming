for ((i = 0 ; i < 100 ; i++ )); do
    python gen.py > input.txt
    if [[ $(diff -y --suppress-common-lines <(cat input.txt | python H.check.py) <(cat input.txt | ./a.exe)) ]]; then
        echo "WA, TC in input.txt"
        break
    else
        echo "AC"
    fi
done