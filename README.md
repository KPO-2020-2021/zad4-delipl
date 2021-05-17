
## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `make` to build the desired target.

Requirements: cmake, gnuplot, doxygen + dot

Example:

``` bash
> mkdir build && cd build
> cmake .. # options: -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release], Debug is default
> make
> ./main
> make fulltest      # Makes and runs the tests.
> make coverage  # Generate a coverage report.
> make doc       # Generate html documentation.
```

Things to remember:
* changes to zad3/CMakeLists.txt with new files added, i.e.:
```cmake
# --------------------------------------------------------------------------------
#                         Locate files (change as needed).
# --------------------------------------------------------------------------------
file(GLOB SOURCES ./src/*.cpp) # All .cpp files in src/

file(GLOB TEST_FILES ./tests/*.ut.cpp)       # All .cpp files in tests/

add_library(SOURCES_LIB OBJECT ${SOURCES})
```
The `main.cpp` in the folder `tests` is needed. Only there we define `#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN`.

The main loop of the program is in the `app` folder.

