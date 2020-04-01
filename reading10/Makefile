CC=             gcc
CFLAGS=         -g -gdwarf-2 -Wall -std=gnu99
TARGETS=        sort grep

all:            $(TARGETS)

# TODO: Add rules for sort and grep

test:
	        @$(MAKE) -sk test-all

test-all:	test-sort test-grep

test-sort:	sort
	curl -sLOk https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/reading10/test_sort.sh
	chmod +x test_sort.sh
	./test_sort.sh

test-grep:	grep
	curl -sLOk https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/reading10/test_grep.sh
	chmod +x test_grep.sh
	./test_grep.sh

clean:
	rm -f $(TARGETS)

.SUFFIXES:
