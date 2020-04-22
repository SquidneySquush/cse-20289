#!/bin/bash

DUPLICATES=bin/duplicates
WORKSPACE=/tmp/duplicates.$(id -u)
FAILURES=0

export LC_ALL=C # Use POSIX locale

# Functions

error() {
    echo "$@"
    [ -s $WORKSPACE/test ] && (echo; cat $WORKSPACE/test; echo)
    FAILURES=$((FAILURES + 1))
}

cleanup() {
    STATUS=${1:-$FAILURES}
    rm -fr $WORKSPACE
    exit $STATUS
}

# Main Execution

export LD_LIBRARY_PATH=$LD_LIBRRARY_PATH:.

mkdir $WORKSPACE
mkdir -p $WORKSPACE/joshi
mkdir -p $WORKSPACE/yoshi
mkdir -p $WORKSPACE/method
echo "black"  >> $WORKSPACE/joshi/tea
echo "black"  >> $WORKSPACE/yoshi/coffee
echo "spiral" >> $WORKSPACE/method/risk
echo "spiral" >> $WORKSPACE/method/alternative

trap "cleanup" EXIT
trap "cleanup 1" INT TERM

echo "Testing duplicates..."

printf " %-40s ... " "duplicates -h"
$DUPLICATES -h < /dev/null 2>&1 | grep -q -i 'usage' &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

## None -----------------------------------------------------------------------

ARGUMENTS="README.md Makefile"
printf " %-40s ... " "duplicates none"
valgrind --leak-check=full $DUPLICATES $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(grep 'duplicate of' $WORKSPACE/test | wc -l) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates none (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates none -c"
valgrind --leak-check=full $DUPLICATES -c $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(grep -v '^==' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates none -c (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates none -q"
valgrind --leak-check=full $DUPLICATES -q $ARGUMENTS &> $WORKSPACE/test
if [ $? -eq 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates none -q (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

## One ------------------------------------------------------------------------

ARGUMENTS="README.md Makefile README.md"
printf " %-40s ... " "duplicates one"
valgrind --leak-check=full $DUPLICATES $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(grep 'duplicate of' $WORKSPACE/test | wc -l) -ne 1 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates one (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates one -c"
valgrind --leak-check=full $DUPLICATES -c $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(grep -v '^==' $WORKSPACE/test) -ne 1 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates one -c (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates one -q"
valgrind --leak-check=full $DUPLICATES -q $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates one -q (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

## Two ------------------------------------------------------------------------

ARGUMENTS="README.md Makefile README.md Makefile"
printf " %-40s ... " "duplicates two"
valgrind --leak-check=full $DUPLICATES $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(grep 'duplicate of' $WORKSPACE/test | wc -l) -ne 2 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates two (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates two -c"
valgrind --leak-check=full $DUPLICATES -c $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(grep -v '^==' $WORKSPACE/test) -ne 2 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates two -c (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates two -q"
valgrind --leak-check=full $DUPLICATES -q $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates two -q (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

## None bin -------------------------------------------------------------------

ARGUMENTS="README.md Makefile bin src"
printf " %-40s ... " "duplicates none dirs"
valgrind --leak-check=full $DUPLICATES $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(grep 'duplicate of' $WORKSPACE/test | wc -l) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates none dirs (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates none dirs -c"
valgrind --leak-check=full $DUPLICATES -c $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(grep -v '^==' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates none dirs -c (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates none dirs -q"
valgrind --leak-check=full $DUPLICATES -q $ARGUMENTS &> $WORKSPACE/test
if [ $? -eq 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates none dirs -q (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

## One bin --------------------------------------------------------------------

ARGUMENTS="README.md Makefile bin $DUPLICATES src"
printf " %-40s ... " "duplicates one dirs"
valgrind --leak-check=full $DUPLICATES $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(grep 'duplicate of' $WORKSPACE/test | wc -l) -ne 1 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates one dirs (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates one dirs -c"
valgrind --leak-check=full $DUPLICATES -c $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(grep -v '^==' $WORKSPACE/test) -ne 1 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates one dirs -c (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates one dirs -q"
valgrind --leak-check=full $DUPLICATES -q $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates one dirs -q (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

## etc ------------------------------------------------------------------------

ARGUMENTS="src bin $WORKSPACE README.md"
printf " %-40s ... " "duplicates two dirs"
valgrind --leak-check=full $DUPLICATES $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(grep 'duplicate of' $WORKSPACE/test | wc -l) -ne 2 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates two dirs (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates two dirs -c"
valgrind --leak-check=full $DUPLICATES -c $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ] || [ $(grep -v '^==' $WORKSPACE/test) -ne 2 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates two dirs -c (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates two dirs -q"
valgrind --leak-check=full $DUPLICATES -q $ARGUMENTS &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "duplicates two dirs -q (valgrind)"
if [ $? -ne 0 ] || [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

## Summary --------------------------------------------------------------------

TESTS=$(($(grep -c Success $0) - 1))

echo
echo "   Score $(echo "scale=4; ($TESTS - $FAILURES) / $TESTS.0 * 6.0" | bc | awk '{ printf "%0.2f\n", $1 }' )"
echo
