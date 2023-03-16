CC=g++
CFLAGS= -Wall -Wextra -Wpedantic -g -Werror
NAME =  merge_sort
CNAME = merge_sort.cpp
ONAME = merge_sort.o

objs:
	$(CC) $(CFLAGS) -c $(CNAME)

all: objs
	$(CC) $(CFLAGS) $(ONAME) -o $(NAME)

re: delete all

all_objs_delete:
	find . -type f -name '*.o' -exec rm {} +
executables_delete:
	find . -type f -executable -exec rm {} +

delete: all_objs_delete executables_delete