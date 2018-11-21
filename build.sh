set -e
mkdir build-cmake
cd build-cmake
cmake .. && make
cp kernel.elf ../iso/boot/kernel.elf
cd ..
rm os.iso
make os.iso
make run
