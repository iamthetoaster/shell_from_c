CC = gcc

NAME = $(shell basename $(CURDIR))

COMPILER_FLAGS = -Wall
LINKER_FLAGS =

SOURCES = $(wildcard *.c)
OBJECTS = $(subst .c,.o,$(SOURCES))

.PHONY: clean

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LINKER_FLAGS)

%.o : %.c
	$(CC) $(COMPILER_FLAGS) -c $<

clean :
	rm -rf *.o $(NAME)
