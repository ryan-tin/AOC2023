CC = g++
CFLAGS = -Wall -g

.PHONY = 1 2

.DEFAULT_GOAL := 2

# $@ name of target
# $^ all prerequisites
# $< first prerequisite
1: part1.cpp
	$(CC) $(CFLAGS) $^ -o $@.o

2: part2.cpp
	$(CC) $(CFLAGS) $^ -o $@.o

clean:
	$(RM) -rf *.o *.dSYM/
