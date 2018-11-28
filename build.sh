set -e
mkdir -p build-cmake
cd build-cmake
cmake .. && make
cd -
make os.iso