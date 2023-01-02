python3 case.py case.in 10
python3 case.py case1.in 12
python3 case.py case2.in 13
python3 case.py case3.in 25
python3 case.py case4.in 100
python3 case.py case5.in 1000
gcc -o main main.cpp

./main case.in case.out 9999
./main case1.in case1.out 9999
./main case2.in case2.out 9999
./main case3.in case3.out 9999
./main case4.in case4.out 9999
./main case5.in case5.out 9999
