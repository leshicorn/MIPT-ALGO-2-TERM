CC=g++
CFLAGS= -Wall -Wextra -Wpedantic -g -lz
NAME =  open_hash_different_chances
CNAME = open_hash_different_chances.cpp
ONAME = open_hash_different_chances.o

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

text_delete:
	find . -type f -name '*.txt' -exec rm {} +