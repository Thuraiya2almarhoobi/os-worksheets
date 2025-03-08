# Define variables
AS = nasm
CC = gcc
LD = ld
ISO_GEN = genisoimage
QEMU = qemu-system-i386

# Compiler and linker flags
ASFLAGS = -f elf
CFLAGS = -m32 -nostdlib -ffreestanding -Idrivers
LDFLAGS = -T source/link.ld -melf_i386

# Directories and files
SRC_DIR = source
DRIVERS_DIR = drivers
ISO_DIR = iso
BOOT_DIR = $(ISO_DIR)/boot
GRUB_DIR = $(BOOT_DIR)/grub
KERNEL = kernel.elf
ISO = os.iso
LOG = logQ.txt

# Source files
ASM_SRC = $(SRC_DIR)/loader.asm $(DRIVERS_DIR)/io.asm
C_SRC = $(SRC_DIR)/kmain.c $(DRIVERS_DIR)/framebuffer.c
ASM_OBJ = $(ASM_SRC:.asm=.o)
C_OBJ = $(C_SRC:.c=.o)

# GRUB files (ensure stage2_eltorito is in the correct path)
GRUB_STAGE2 = $(GRUB_DIR)/stage2_eltorito

# Targets
.PHONY: all clean run

# Default target
all: $(ISO)

# Compile assembly files
%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link kernel
$(KERNEL): $(ASM_OBJ) $(C_OBJ)
	$(LD) $(LDFLAGS) $(ASM_OBJ) $(C_OBJ) -o $@

# Copy kernel to ISO directory
$(BOOT_DIR)/$(KERNEL): $(KERNEL)
	mkdir -p $(BOOT_DIR)
	cp $(KERNEL) $(BOOT_DIR)/

# Create ISO
$(ISO): $(BOOT_DIR)/$(KERNEL) $(GRUB_STAGE2)
	mkdir -p $(GRUB_DIR)
	$(ISO_GEN) -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os \
	-input-charset utf8 -quiet -boot-info-table -o $@ $(ISO_DIR)

# Run in QEMU
run: $(ISO)
	$(QEMU) -curses -monitor telnet::35467,server,nowait -serial mon:stdio \
	-boot d -cdrom $(ISO) -m 32 -d cpu -D $(LOG)

# Clean up generated files
clean:
	rm -rf $(SRC_DIR)/*.o $(DRIVERS_DIR)/*.o $(KERNEL) $(ISO) $(ISO_DIR)