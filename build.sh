set -e
mkdir -p build-cmake
cd build-cmake
cmake .. && make
mkdir -p ../iso/boot
cp -f kernel.elf ../iso/boot/kernel.elf
cd ..
if [ -f os.iso ] 
then
    rm os.iso
fi
make os.iso