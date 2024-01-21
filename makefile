CC = gcc
CFLAGS = -Wall -I$(INCLUDES)
INCLUDES = ./header
SRCDIR = ./src

# Define SRC to include all .c files in the source directory
#SRC = $(wildcard $(SRCDIR)/*.c)

SRC = $(SRCDIR)/grammarparser.c $(SRCDIR)/grammarformatparser.c $(SRCDIR)/stringutils.c $(SRCDIR)/stack.c $(SRCDIR)/main.c 

OBJ = $(SRC:.c=.o)

EXECUTABLE = grm

# Default target
all: $(EXECUTABLE)

# Build rule for the executable
$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^

# Dependencies
$(SRCDIR)/main.o : $(SRCDIR)/grammarparser.o $(SRCDIR)/grammarformatparser.o
$(SRCDIR)/grammarparser.o $(SRCDIR)/grammarformatparser.o : $(SRCDIR)/stack.o $(SRCDIR)/stringutils.o

# Rule for creating object files
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Clean rule
clean:
	rm -f $(SRCDIR)/*.o $(EXECUTABLE)

# PHONY targets
.PHONY: all clean
