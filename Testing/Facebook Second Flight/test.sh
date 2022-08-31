python genForSecondFlight.py 
echo "generated"

echo "Python time to follow:"
time (cat inputGraph.txt | python checkSecondFlight.py > outputPython.txt)
echo "Python done"

echo "C++ time to follow"
time (cat inputGraph.txt | ./a.out  > outputC++.txt)
echo "C++ done"

echo "See differences below:"
diff outputPython.txt outputC++.txt
