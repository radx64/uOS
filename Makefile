BUILD_DIR = build-cmake/
SOURCE_DIR = src
KERNEL_BINARY_NAME = kernel.elf
KERNEL_BINARY_PATH = $(BUILD_DIR)$(KERNEL_BINARY_NAME)

.PHONY: clean
clean:
	rm -rf build-cmake/ iso/ os.iso

os.iso:
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

run:
	qemu-system-x86_64 -boot d -cdrom os.iso -m 32M -serial stdio -cpu base

