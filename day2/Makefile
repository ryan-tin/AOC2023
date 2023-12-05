CC=g++
CFLAGS=-g -Wall
EXEC=day2
OBJ=$(EXEC).o
DIRS=./
DEPS=

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

db:
	lldb $(DIRS)$(EXEC)

clean:
	$(RM) -rf *.o *.dSYM/ $(EXEC)

all: clean $(EXEC)
