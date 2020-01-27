#!/bin/bash

set -e -u -x -o pipefail

# install vcpkg with HDF5 and nlohmann/json
[ -d vcpkg ] || git clone https://github.com/microsoft/vcpkg.git
[ -f vcpkg/vcpkg ] || (cd vcpkg && ./bootstrap-vcpkg.sh -disableMetrics)
[ -f vcpkg/installed/x64-linux/lib/libhdf5.a ] || vcpkg/vcpkg install hdf5
[ -f vcpkg/installed/x64-linux/include/nlohmann/json.hpp ] || vcpkg/vcpkg install nlohmann-json

# build CompiledNN predicter
# rm -Rf build
mkdir -p build
cd build
cmake \
    -G Ninja \
    -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_SHARED_LIBS=OFF \
    -DWITH_APPLICATIONS=ON \
    -DWITH_TESTS=OFF \
    -DWITH_COVERAGE=OFF \
    ..
cmake --build .

cp Predicter ..
