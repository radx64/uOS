BUILD_DIR = build/
SOURCE_DIR = src/
KERNEL_BINARY_NAME = kernel.elf
KERNEL_BINARY_PATH = $(BUILD_DIR)$(KERNEL_BINARY_NAME)

OBJECTS = $(SOURCE_DIR)loader.o $(SOURCE_DIR)kmain.o $(SOURCE_DIR)io.o \
 $(SOURCE_DIR)framebuffer.o		
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	     -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -std=c99
LDFLAGS = -T $(SOURCE_DIR)link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: $(KERNEL_BINARY_PATH)

$(KERNEL_BINARY_PATH): $(OBJECTS)
	mkdir -p $(BUILD_DIR)
	ld $(LDFLAGS) $(OBJECTS) -o $(KERNEL_BINARY_PATH)

.PHONY: configure
configure:
	sudo apt-get update
	sudo apt-get install -y build-essential nasm genisoimage bochs bochs-sdl

.PHONY: clean
clean:
	rm -rf build/ iso/ os.iso

os.iso: $(KERNEL_BINARY_PATH)
	mkdir -p iso/boot/grub
	cp grub/stage2 iso/boot/grub
	cp grub/menu.lst iso/boot/grub 
	cp $(KERNEL_BINARY_PATH) iso/boot/kernel.elf

	genisoimage -R					 \
			-b boot/grub/stage2  \
			-no-emul-boot        \
			-boot-load-size 4    \
			-A os                \
			-input-charset utf8  \
			-quiet               \
			-boot-info-table     \
			-o os.iso            \
			iso

run: os.iso
	bochs -q -f bochsConfig.txt

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@


