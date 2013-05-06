#Rebecca Hoberg
#CSE 374 Winter 2013
# Makefile for project

#default target
t9: t9.o Node.o
  gcc -Wall -g -o t9 t9.o Node.o

# individual source files
t9.o: Node.h t9.c
	gcc -Wall -g -c t9.c

Node.o: Node.h Node.c
	gcc -Wall -g -c Node.c
