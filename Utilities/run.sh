# After sorting test cases by extension, run all test cases and diff

files=$(ls cases/in | sort -n)
for file in $files
do
    IFS='.' read -ra ADDR <<< "$file"
    base=${ADDR[0]}
    ext=${ADDR[1]}

    echo "$base"
    diff --suppress-common-lines -y <(cat "cases/ans/$base.ans" | python script.py) <(cat "cases/in/$base.in"  | python A2.py)
done