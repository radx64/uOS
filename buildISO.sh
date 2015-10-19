#!/bin/bash
mkdir -p iso/boot/grub			# create folder structure
cp grub/stage2 iso/boot/grub	# copy bootloader
cp grub/menu.lst iso/boot/grub  # copy bootloader config
cp build/kernel.elf iso/boot    # copy the kernel

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