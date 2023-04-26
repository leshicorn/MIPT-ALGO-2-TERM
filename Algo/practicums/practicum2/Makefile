CC=gcc
CFLAGS= -Wall -Wextra -Wpedantic -g
NAME_LIST =  stack_list
CNAME_LIST = stack_list.c
ONAME_LIST = stack_list.o

NAME_ARRAY = stack_array
CNAME_ARRAY = stack_array.c
ONAME_ARRAY = stack_array.o

objs_list:
	$(CC) $(CFLAGS) -c $(CNAME_LIST)

all_l: objs_list
	$(CC) $(CFLAGS) $(ONAME_LIST) -o $(NAME_LIST)

objs_array:
	$(CC) $(CFLAGS) -c $(CNAME_ARRAY)

all_a: objs_array
	$(CC) $(CFLAGS) $(ONAME_ARRAY) -o $(NAME_ARRAY)

all: all_l all_a

all_objs_delete:
	find . -type f -name '*.o' -exec rm {} +
executables_delete:
	find . -type f -executable -exec rm {} +

delete: all_objs_delete executables_delete