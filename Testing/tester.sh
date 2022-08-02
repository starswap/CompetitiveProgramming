#!/bin/bash
> pythonOut.txt
> cppOut.txt

for value in {30..50}
do
python main.py $value
cat input.txt | python solve.py >> pythonOut.txt
cat input.txt | ./a.out >> cppOut.txt
done
echo Done!

diff pythonOut.txt cppOut.txt
