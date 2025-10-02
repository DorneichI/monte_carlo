# Makefile for Monte Carlo project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11 -O2

# Target executable
TARGET = main

# Source files
SRCS = main.c monte_carlo.c random.c

# Header files
HDRS = monte_carlo.h random.h

# Object files
OBJS = $(SRCS:.c=.o)

# Add GSL library flags
GSL_CFLAGS = $(shell gsl-config --cflags)
GSL_LIBS = $(shell gsl-config --libs)

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(GSL_CFLAGS) -o $@ $(OBJS) $(GSL_LIBS)

# Compile source files into object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(GSL_CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean