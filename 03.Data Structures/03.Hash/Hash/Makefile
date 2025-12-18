# Makefile for Algorithm Templates (Cross-platform: Windows/MacOS)

# Setting the compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2 -std=c11

# Detect OS
ifdef OS
    DETECTED_OS = Windows
else
    DETECTED_OS = Unix
endif

# Target executable name and commands
ifeq ($(DETECTED_OS),Windows)
    TARGET = Hash.exe
    RM = powershell -Command "Remove-Item -ErrorAction SilentlyContinue"
    RUN = .\$(TARGET)
else
    TARGET = Hash
    RM = rm -f
    RUN = ./$(TARGET)
endif

# Source files
SRCS = main.c	\
		Hash.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Linking the object files to create the executable
$(TARGET): $(OBJS)
	@echo Building $(TARGET)...
	$(CC) $(CFLAGS) -o $@ $^
	@echo Build complete!

# Compiling source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	@echo Running $(TARGET)...
	@$(RUN)

clean:
	@echo Cleaning object files...
	-@$(RM) *.o
	@echo Clean complete!

fclean: clean
	@echo Removing executable...
	-@$(RM) $(TARGET)
	@echo Full clean complete!

re: fclean all

debug: CFLAGS += -g -DDEBUG
debug: fclean all

help:
	@echo Available commands:
	@echo   make         - Build the project
	@echo   make run     - Build and run the project
	@echo   make clean   - Remove object files
	@echo   make fclean  - Remove object files and executable
	@echo   make re      - Rebuild everything
	@echo   make debug   - Build with debug information
	@echo   make help    - Show this help message

.PHONY: all clean fclean re debug help run