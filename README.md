
## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `make` to build the desired target.

Requirements: cmake, gnuplot, doxygen + dot

Build commands

``` bash
 git submodule init doctest
 git submodule update
 
 mkdir build && cd build
 cmake ..           # options: -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release], Debug is default
 make app           # Runs main loop
 make fulltest      # Makes and runs the tests.
 make coverage      # Generate a coverage report.
 make doc           # Generate html documentation.
```

The `main.cpp` in the folder `tests` is needed. Only there we define `#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN`.

The main loop of the program is in the `app` folder.

