# Build Notes

The project uses CMake and SDL2.

Typical local workflow:

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
ctest --output-on-failure
```

The CMake configuration copies `assets/` into the build directory so the executable can also be launched from `build/`.
