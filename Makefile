# Compiler
CC = gcc
# CLINK
CCLINK = $(CC)
# Compiler flags
CFLAGS = -g -Wall -std=c99

RM = rm -rf


libgrades.so: grades.o
	$(CCLINK) -shared grades.o -o libgrades.so -llinked-list -L.
	$(RM) grades.o

grades.o: linked-list.h grades.h grades.c
	$(CC) $(CFLAGS) -c -fPIC grades.c

clean:
	$(RM) grades.o libgrades.so


