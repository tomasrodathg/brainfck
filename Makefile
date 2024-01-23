# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Source and test directories
SRC_DIR = src

# Source and object files for the application
APP_SRC = $(wildcard $(SRC_DIR)/*.c)
APP_OBJ = $(APP_SRC:.c=.o)

# Output binaries
BIN = brainfck

# Check library
CHECK_LIBS = `pkg-config --libs check`

all: $(BIN)

$(BIN): $(APP_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(BIN) $(APP_OBJ) 

