cd build-cmake
cmake .. && make
cd src
ld libloader_asm.a libsrc.a libasm_src.a -T ../../src/link.ld -melf_i386 -o kernel.elf
cp kernel.elf ../../iso/boot/kernel.elf
cd ../..
rm os.iso
make os.iso
make run
