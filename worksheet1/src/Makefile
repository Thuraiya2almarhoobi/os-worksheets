# Define the compiler and assembler
CC = gcc
ASM = nasm

# Compiler and assembler flags
CFLAGS = -m32 -c
AFLAGS = -f elf32

# Target executables
TARGET1 = task1
TARGET2 = task2
TARGET2_2 = task2.2

# Object files for each task
OBJS1 = task1.o asm_io.o driver.o
OBJS2 = task2.o asm_io.o driver.o
OBJS2_2 = task2.2.o asm_io.o driver.o

# Default target to build all tasks
all: $(TARGET1) $(TARGET2) $(TARGET2_2)

# Rule to build Task 1 executable
$(TARGET1): $(OBJS1)
	$(CC) -m32 -o $(TARGET1) $(OBJS1)

# Rule to build Task 2 executable
$(TARGET2): $(OBJS2)
	$(CC) -m32 -o $(TARGET2) $(OBJS2)

# Rule to build Task 2.2 executable
$(TARGET2_2): $(OBJS2_2)
	$(CC) -m32 -o $(TARGET2_2) $(OBJS2_2)

# Rule to assemble task1.asm
task1.o: task1.asm
	$(ASM) $(AFLAGS) task1.asm -o task1.o

# Rule to assemble task2.asm
task2.o: task2.asm
	$(ASM) $(AFLAGS) task2.asm -o task2.o

# Rule to assemble task2.2.asm
task2.2.o: task2.2.asm
	$(ASM) $(AFLAGS) task2.2.asm -o task2.2.o

# Rule to assemble asm_io.asm
asm_io.o: asm_io.asm
	$(ASM) $(AFLAGS) asm_io.asm -o asm_io.o

# Rule to compile driver.c
driver.o: driver.c
	$(CC) $(CFLAGS) driver.c -o driver.o

# Clean up build artifacts
clean:
	rm -f *.o $(TARGET1) $(TARGET2) $(TARGET2_2)

# Ensure clean and all are treated as phony targets
.PHONY: clean all
