CC=             gcc
CFLAGS=         -g -Wall -std=gnu99
TARGETS=        str_title

all:            $(TARGETS)

# TODO: Add rule for str_title
str_title: str_title.c
	$(CC) $(CFLAGS) -o str_title str_title.c

test:
	        @$(MAKE) -sk test-all

test-all:	test-str_title

test-str_title:	str_title
	curl -sLO https://gitlab.com/nd-cse-20289-sp20/cse-20289-sp20-assignments/raw/master/reading11/test_str_title.sh
	chmod +x test_str_title.sh
	./test_str_title.sh

clean:
	rm -f $(TARGETS)

.SUFFIXES:
