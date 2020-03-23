test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-walk test-doit

test-scripts:
	curl -sLO https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/reading08/test_walk.sh
	curl -sLO https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/reading08/test_doit.sh
	chmod +x test_*.sh

test-walk:
	./test_walk.sh

test-doit:
	./test_doit.sh
