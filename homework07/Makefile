test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-moveit test-timeit test-quiz

test-scripts:
	curl -sLO https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/homework07/test_moveit.sh
	curl -sLO https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/homework07/test_timeit.sh
	curl -sLO https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/homework07/test_quiz.py
	chmod +x test_moveit.sh test_timeit.sh test_quiz.py

test-moveit:
	./test_moveit.sh

test-timeit:
	./test_timeit.sh

test-quiz:
	./test_quiz.py
