CC=             gcc
CFLAGS=         -g -gdwarf-2 -Wall -std=gnu99
TARGETS=        sort grep

all:            $(TARGETS)

# TODO: Add rules for sort and grep
sort_.c:		sort.c
			cpp sort.c > sort_c

sort.s:	sort_.c
	@echo "Compiling..."
	gcc -o sort.s -S sort_.c

sort.o:	sort.s
	@echo "Assembling..."
	as -o sort.o sort.s

sort.exe:	sort.o
	@echo "Linking..."
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o sort.exe /usr/lib64/crt1.o /usr/lib64/crti.o sort.o -lc /usr/lib64/crtn.o



grep:


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
