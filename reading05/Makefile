test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-exists

test-scripts:
	curl -sLO https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/reading05/test_exists.sh
	chmod +x test_*.sh

test-exists:
	./test_exists.sh
