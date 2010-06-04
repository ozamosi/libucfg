.PHONY: clean


all: example.c ucfg.c ucfg.h
	gcc example.c ucfg.c -ggdb -Wall -Wextra -pedantic -ansi -o example -g

test: ucfg.c ucfg.h test.c
	gcc ucfg.c test.c -Wall -Wextra -pedantic -ansi -D_POSIX_C_SOURCE=1 -o test -g
	./test

clean:
	rm -f example example.conf
