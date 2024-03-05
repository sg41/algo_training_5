#!/bin/bash
run_test(){
    local TEST="$1 $2 $3"
    echo $TEST
    local RES=`echo $TEST | ./a.out`
    [[ $RES -eq $4 ]] || echo "$RES != $4"
}

g++ -std=c++20 -g g.cpp

run_test 1 1 1 1
run_test 1 2 1 -1
run_test 10 11 15 4
run_test 300 301 485 -1
run_test 300 301 484 6
run_test 250 500 230 8
run_test 5 8 5 4
run_test 25 200 10 13
run_test 250 500 187 4
run_test 250 500 218 6
run_test 2 3 2 3
run_test 250 500 249 101
run_test 8 12 7 3
run_test 2500 5000 2499 961
run_test 78 4934 77 4812
run_test 78 126 77 5
run_test 1661 4327 1107 6
run_test 1092 2892 950 11
run_test 31 495 15 30
run_test 250 500 209 6
run_test 3000 5000 2998 79
run_test 2500 5000 2420 16