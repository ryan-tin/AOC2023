CC=g++
CFLAGS=-g -Wall
CVER=-std=c++20
EXEC=day2
OBJ=$(EXEC).o
DIRS=./
DEPS=

%.o: %.cpp $(DEPS)
	$(CC) $(CVER) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJ)
	$(CC) $(CVER) $(CFLAGS) $^ -o $@

db:
	lldb $(DIRS)$(EXEC)

clean:
	$(RM) -rf *.o *.dSYM/ $(EXEC)

all: clean $(EXEC)
