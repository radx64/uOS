set -e
mkdir -p build-cmake
cd build-cmake
cmake .. && make
cd -
if [ -f os.iso ]
then
    rm os.iso -rf
fi
make os.iso