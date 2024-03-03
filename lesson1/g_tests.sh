#!/bin/bash
run_test(){
    local TEST="$1 $2 $3"
    echo $TEST
    local RES=`echo $TEST | ./a.out`
    [[ $RES -eq $4 ]] || echo "$RES != $4"
}

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