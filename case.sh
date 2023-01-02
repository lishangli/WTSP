#!/bin/bash
case1=$1
N=$2
C=$3
echo ${case1}
python3 case.py ${case1}".in" ${N}
# python3 case.py case1.in 12
# python3 case.py case2.in 13
# python3 case.py case3.in 25
# python3 case.py case4.in 100
# python3 case.py case5.in 1000
g++ main.cpp -o main

./main ${case1}".in" ${case1}".out" ${C}
# ./main case1.in case1.out 9999
# ./main case2.in case2.out 9999
# ./main case3.in case3.out 9999
# ./main case4.in case4.out 9999
# ./main case5.in case5.out 9999
