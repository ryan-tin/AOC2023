CC=g++
CVER=-std=c++20
CFLAGS=-g -Wall
EXEC=day4
OBJ=$(EXEC).o
DIRS=./
# header files go in DEPS
DEPS= 

# object files depend on their cpp and header files
%.o: %.cpp $(DEPS)
	$(CC) $(CVER) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJ)
	$(CC) $(CVER) $(CFLAGS) $^ -o $@

db:
	lldb $(DIRS)$(EXEC)

clean:
	$(RM) -rf *.o *.dSYM/ $(EXEC)

all: clean $(EXEC)
