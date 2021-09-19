BUILD_DIR = build/
SOURCE_DIR = src
KERNEL_BINARY_NAME = src/kernel.elf
KERNEL_BINARY_PATH = $(BUILD_DIR)$(KERNEL_BINARY_NAME)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) iso/ os.iso

os.iso:
	echo "\033[32;1;1mPreparing GRUB bootloader...\033[0m"
	mkdir -p iso/boot/grub
	cp grub/stage2 iso/boot/grub
	cp grub/menu.lst iso/boot/grub 
	echo "\033[32;1;1mCopying kernel...\033[0m"
	cp $(KERNEL_BINARY_PATH) iso/boot/kernel.elf
	echo "\033[32;1;1mGenerating ISO image...\033[0m"
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

run:
	qemu-system-x86_64 -boot d -cdrom os.iso -m 32M -serial stdio

