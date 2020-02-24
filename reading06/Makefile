test:
	@$(MAKE) -sk test-all

test-all:	test-scripts

test-scripts:
	curl -sLO https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/reading06/test_scripts.sh
	chmod +x test_scripts.sh
	./test_scripts.sh
