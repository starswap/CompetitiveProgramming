# sorts test cases by extension

files=$(ls cases)
for file in $files
do
    IFS='.' read -ra ADDR <<< "$file"
    base=${ADDR[0]}
    ext=${ADDR[1]}
    if [ "$ext" = "in" ];
    then
        mv "cases/$file" "cases/in/$file"
    elif [ "$ext" = "ans" ];
    then
        mv "cases/$file" "cases/ans/$file"
    fi
done