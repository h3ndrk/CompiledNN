vcpkg/installed/x64-linux/lib/libhdf5.a: vcpkg/vcpkg
	./vcpkg install hdf5

vcpkg/installed/x64-linux/include/nlohmann/json.hpp: vcpkg/vcpkg
	./vcpkg install nlohmann-json

vcpkg/vcpkg: vcpkg
	cd vcpkg && ./bootstrap-vcpkg.sh -disableMetrics

vcpkg:
	git clone https://github.com/microsoft/vcpkg.git
