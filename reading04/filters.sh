#!/bin/bash

q1_answer() {
    # TODO: List only the names of the turtles in sorted order.
    curl -sL https://yld.me/raw/lE8 | sort | cut -d ':' -f 1
}

q2_answer() {
    # TODO: List only the colors of the turtles in all capitals.
    curl -sL https://yld.me/raw/lE8 | cut -d ':' -f 2 | tr 'a-z' 'A-Z'
}

q3_answer() {
    # TODO: Replace all weapons with plowshares
    curl -sL https://yld.me/raw/lE8 | sed -E 's/(katana|bo|sai|nunchucks)/plowshare/g' 
}

q4_answer() {
    # TODO: List only the turtles whose names end in lo.
    curl -sL https://yld.me/raw/lE8 | cut -d ':' -f 1 | grep -e 'lo$'
}

q5_answer() {
    # TODO: List only the turtles with names that have two consecutive vowels.
     curl -sL https://yld.me/raw/lE8 | cut -d ':' -f 1 | grep -E '[aeiou]{2}'
}

q6_answer() {
    # TODO: Count how many colors don't begin with a vowel
    curl -sL https://yld.me/raw/lE8 | cut -d ':' -f 2 | grep -Ev '^[aeiou]' | wc -l
}

q7_answer() {
    # TODO: List only the turtles names whose name ends with a vowel and whose weapon ends with a vowel.
    curl -sL https://yld.me/raw/lE8 | grep -E '[aeiou]$' | cut -d ':' -f 1 | grep -E '[aeiou]$'
}

q8_answer() {
    # TODO: List only the turtles names with two of the same consecutive letter (i.e. aa, bb, etc.)
    curl -sL https://yld.me/raw/lE8 | grep -E '(.)*\1' | cut -d ':' -f 2
}
