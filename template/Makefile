# Makefile for Alogrithm Templates (Cross-platform: Windows/MacOS)

# Setting the compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -02 -std=c11

# Target executable name
ifeq ($(OS),Windows_NT)
	TARGE = algorithm.exe
	RM = del /Q
else
	TARGET = algorithm
	RM = rm -f
endif

# Source files
SRCS = main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Linking the object files to create the executable
$(TARGET): $(OBJS)
	@echo "Building $(TARGET)..."
	@$(CC) $(CFLAGS) -o $@ $^

# Compiling source files to object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

run: all
	@echo "Running $(TARGET)..."
	@./$(TARGET)

clean:
	ifeq ($(OS),Windows_NT)
		$(RM) *.o
	else
		$(RM) *.o

fclean: clean
	$(RM) $(TARGET)

debug: CFLAGS += -g -DDEBUG
debug: clean all

help:
	@echo "Available commands:"
	@echo " make		  - Build the project"
	@echo " make run	  - Build and run the project"
	@echo " make clean	  - Remove object files"
	@echo " make fclean	  - Remove object files and executable"
	@echo " make debug	  - Build with debug information"
	@echo " make help	  - Show this help message"

re :
	@make fclean
	@make all

.PHONY: all clean fclean re
