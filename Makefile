CFLAGS=-ggdb -Wall -Wextra

tests: test_linkedlist test_parser test_lexer

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

lexer: lexer.h lexer.c linkedlist.o parser.o
	gcc $(CFLAGS) -c lexer.c

test_lexer: lexer.o test_lexer.c parser.o linkedlist.o
	gcc $(CFLAGS) -c test_lexer.c
	gcc $(CFLAGS) -o test_lexer test_lexer.o lexer.o parser.o linkedlist.o

clean:
	rm -f *.o

realclean: clean
	rm -f test_parser
	rm -f test_linkedlist
	rm -f test_lexer
