CC=g++
CFLAGS=-g -Wall
EXEC=temp
OBJ=$(EXEC).o
DIRS=./

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

db:
	lldb $(DIRS)$(EXEC)

clean:
	$(RM) -rf *.o *.dSYM/ $(EXEC)
