# berkeley-db-cpp-framework build
C++ framework for Berkeley DB can be built with these instructions:
- Follow the instructions in INSTALL.db to install the necessary software
- Build using Clion, or run from the command line, 
```
$ cmake -B build -S .
$ cd build
$ make
```
- Build the Doxygen html documentation files with:
```
$ cmake --build build --target docs
```
(use `cmake-build-debug` instead of `build` if using Clion).
The Doxygen html files will be in `src/build/_build/html`.
- Run this to test the build:
```
$ sh run.sh
```
