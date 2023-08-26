CASES="data"
files=$(ls $CASES)
# echo $files
mkdir $CASES/in
mkdir $CASES/ans
for file in $files
do
    echo $file
    IFS='.' read -ra ADDR <<< "$file"
    base=${ADDR[0]}
    ext=${ADDR[1]}
    if [ "$ext" = "in" ];
    then
        mv "$CASES/$file" "$CASES/in/$file"
    elif [ "$ext" = "ans" ];
    then
        mv "$CASES/$file" "$CASES/ans/$file"
    fi
done
