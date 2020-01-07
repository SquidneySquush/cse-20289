#!/bin/sh

for i in $(seq 1 12); do
    n=$(printf "%02d" $i)

    mkdir exam$n
    mkdir reading$n
    mkdir homework$n

    cat > reading$n/README.md <<EOF
# Reading $n
EOF
    cat > homework$n/README.md <<EOF
# Homework $n
EOF

    cat > exam$n/README.md <<EOF
# Exam $n
EOF
done

rm -fr homework11 homework12
rm -fr exam0[4-9] exam1[0-9]
