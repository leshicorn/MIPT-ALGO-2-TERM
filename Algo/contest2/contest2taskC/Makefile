CC=gcc
CFLAGS= -Wall -Wextra -Wpedantic -g -Wimplicit-function-declaration -std=gnu11
NAME =  c
CNAME = c.c
ONAME = c.o

objs:
	$(CC) $(CFLAGS) -c $(CNAME)

all: objs
	$(CC) $(CFLAGS) $(ONAME) -o $(NAME)

re: delete all

all_objs_delete:
	find . -type f -name '*.o' -exec rm {} +
executables_delete:
	find . -type f -executable -exec rm {} +
assembly_delete:
	find . -type f -name '*.s' -exec rm {} +

delete: all_objs_delete executables_delete assembly_delete