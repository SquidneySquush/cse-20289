#!/bin/bash

q1_answer() {
    # TODO: Complete pipeline
    echo "All your base are belong to us" | tr a-z A-Z
}

q2_answer() {
    # TODO: Complete pipeline
	 echo "monkeys love bananas" | sed 's/monkeys/gorillaz/'
}

q3_answer() {
    # TODO: Complete pipeline

         echo "     monkeys love bananas" | sed -e 's/^[ \t]*//'
}

q4_answer() {
    # TODO: Complete pipeline
	 curl -sL https://yld.me/raw/yWh | grep ^root | cut -d ':' -f 7 
}

q5_answer() {
    # TODO: Complete pipeline
	curl -sL https://yld.me/raw/yWh | sed 's/\/bin\/bash/\/usr\/bin\/python/' | sed 's/\/bin\/csh/\/usr\/bin\/python/' | sed 's/\/bin\/tcsh/\/usr\/bin\/python/'  | grep python
}

q6_answer() {
    # TODO: Complete pipeline
	curl -sL https://yld.me/raw/yWh | grep -e '4[0-9]*7'
}
