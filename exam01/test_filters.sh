#!/bin/bash

if [ ! -r filters.sh ]; then
    echo 'Missing filters.sh!'
    exit 1
else
    . filters.sh
fi

# Utility

q_test() {
    exec 2> log.1

    echo -n "      Q${1} "
    if diff -y <(${2}) <(${3}) &> log.2; then
    	echo 'Success'
    	STATUS=0
    else
    	echo 'Failure'
    	cat log.1 log.2
    	STATUS=1
    fi

    rm log.1 log.2
    return $STATUS
}

# Q1

q1_output() {
    cat <<EOF
Brockman
Bualuan
Bui
Flynn
Joshi
EOF
}

q1_test() {
    q_test 1 q1_answer q1_output
}

# Q2

q2_output() {
    cat <<EOF
5
EOF
}

q2_test() {
    q_test 2 q2_answer q2_output
}

# Q3

q3_output() {
    cat <<EOF
Matt
Siddharth
EOF
}

q3_test() {
    q_test 3 q3_answer q3_output
}

# Q4

q4_output() {
    cat <<EOF
6
EOF
}

q4_test() {
    q_test 4 q4_answer q4_output
}

# Q5

q5_output() {
    cat <<EOF
flynn
skumar5
pbui
rbualuan
sjoshi2
mniemier
EOF
}

q5_test() {
    q_test 5 q5_answer q5_output
}

# Q6

q6_output() {
    cat <<EOF
Jay
Pat
EOF
}

q6_test() {
    q_test 6 q6_answer q6_output
}

# Main execution

SCORE=0

echo "Testing filters.sh ..."
q1_test && SCORE=$((SCORE + 1))
q2_test && SCORE=$((SCORE + 1))
q3_test && SCORE=$((SCORE + 1))
q4_test && SCORE=$((SCORE + 1))
q5_test && SCORE=$((SCORE + 1))
q6_test && SCORE=$((SCORE + 1))

echo "   Score $(echo "scale=2; $SCORE" | bc )"

if [ $SCORE -ge 5 ]; then
    exit 0
else
    exit 1
fi

