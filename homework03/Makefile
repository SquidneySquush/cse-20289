test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-weather test-zipcode test-quiz

test-scripts:
	curl -sLO https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/homework03/test_weather.sh
	curl -sLO https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/homework03/test_zipcode.sh
	curl -sLO https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/homework03/test_quiz.py
	chmod +x test_*.sh test_*.py

test-weather:
	./test_weather.sh

test-zipcode:
	./test_zipcode.sh

test-quiz:
	./test_quiz.py
