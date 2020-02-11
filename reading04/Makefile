test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-filters

test-scripts:
	curl -sLO https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/reading04/test_filters.sh
	chmod +x test_filters.sh

test-filters:
	./test_filters.sh
