CFLAGS=-ggdb -Wall -Wextra

tests: test_linkedlist test_parser test_lexer test_evaluator

test_parser: parser.o test_parser.c linkedlist.o
	gcc $(CFLAGS) -c test_parser.c
	gcc $(CFLAGS) -o test_parser test_parser.o parser.o linkedlist.o

parser: parser.h parser.c linkedlist.h
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

evaluator: evaluator.h evaluator.c lexer.h parser.h linkedlist.h
	gcc $(CFLAGS) -c evaluator.c

test_evaluator: evaluator.o lexer.o parser.o linkedlist.o
	gcc $(CFLAGS) -c test_evaluator.c
	gcc $(CFLAGS) -o test_evaluator test_evaluator.o lexer.o parser.o linkedlist.o evaluator.o

env: env.h env.c
	gcc $(CFLAGS) -c env.c

clean:
	rm -f *.o

realclean: clean
	rm -f test_parser
	rm -f test_linkedlist
	rm -f test_lexer
	rm -f test_evaluator
