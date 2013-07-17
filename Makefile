CFLAGS=-ggdb -Wall -Wextra

test_parser: parser.o test_parser.c
	gcc $(CFLAGS) -c test_parser.c
	gcc $(CFLAGS) -o test_parser test_parser.o parser.o

parser: parser.h parser.c
	gcc $(CFLAGS) -c parser.c
