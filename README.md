
## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `make` to build the desired target.

Requirements: cmake, gnuplot, doxygen + dot

Build commands

``` bash
git clone https://github.com/KPO-2020-2021/zad4-delipl.git # Cloning repository
cd zad4-delipl

git submodule init lib/doctest
git submodule update

mkdir build tmp && cd build
cmake ..           # options: -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release], Debug is default
make fulltest      # Makes and runs the tests.
make coverage      # Generate a coverage report.
make doc           # Generate html documentation.

make app           # Runs main loop
```

The `main.cpp` in the folder `tests` is needed. Only there we define `#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN`.

The main loop of the program is in the `app` folder.

