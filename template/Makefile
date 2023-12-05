CC=g++
CFLAGS=-g -Wall
# TIP: use a substitute command to change temp
EXEC=temp
OBJ=$(EXEC).o
DIRS=./
# header files go in DEPS
DEPS= 

# object files depend on their cpp and header files
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

db:
	lldb $(DIRS)$(EXEC)

clean:
	$(RM) -rf *.o *.dSYM/ $(EXEC)

all: clean $(EXEC)
