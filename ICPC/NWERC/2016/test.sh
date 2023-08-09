for i in {0..50}
do
    py J.gen.py > J.in$i.txt
    echo "Case: $i"
    echo "AC gave: $(cat J.in$i.txt | ./AC.exe)"
    echo "WA gave: $(cat J.in$i.txt | ./WA.exe)"
done