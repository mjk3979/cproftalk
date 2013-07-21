CFLAGS=-ggdb -Wall -Wextra

tests: test_linkedlist test_parser

test_parser: parser.o test_parser.c
	gcc $(CFLAGS) -c test_parser.c
	gcc $(CFLAGS) -o test_parser test_parser.o parser.o

parser: parser.h parser.c
	gcc $(CFLAGS) -c parser.c

linkedlist: linkedlist.h linkedlist.c
	gcc $(CFLAGS) -c linkedlist.c

test_linkedlist: linkedlist.o test_linkedlist.c
	gcc $(CFLAGS) -c test_linkedlist.c
	gcc $(CFLAGS) -o test_linkedlist test_linkedlist.o linkedlist.o
