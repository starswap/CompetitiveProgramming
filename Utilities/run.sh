# After sorting test cases by extension, run all test cases and diff

CASES=data
files=$(ls $CASES/in | sort -n)
for file in $files
do
    IFS='.' read -ra ADDR <<< "$file"
    base=${ADDR[0]}
    ext=${ADDR[1]}

    echo "$base"
    diff --strip-trailing-cr --suppress-common-lines -y <(cat "$CASES/ans/$base.ans") <(cat "$CASES/in/$base.in"  | python J.py)
done

