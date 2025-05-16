# cv-workbench build tools and libraries installation <a id="build-tools-and-libraries-installation"/>
Below are requirements to set up the system to build and run `cv-workbench` for Linux from source.
Once they are in place, the system may be built with:
```
$ sh build.sh
```
This builds the main program `cv-workbench` and some additional utilities.
Successful building verifies that the installation of the system is correct.
## Table of Contents
- [Windows build tools](#windows-build-tools)
  - [WSL2 Linux](#windows-10-wsl2-linux-distributions)
  - [WSL2 Pengwin Linux Distribution](#wsl2-pengwin-distribution)
  - [Windows Terminal](#windows-terminal-tool)
  - [JetBrains CLion](#jetbrains-clion)
- [Linux Build Tools and C++ libraries](#linux-build-tools-and c++-libraries)
  - [Linux compiler tools](#linux-compiler-tools)
  - [Git](#linux-git-tool)
  - [pthreads Library](#linux-pthreads-library)
  - [OpenSSL Library](#linux-openssl-library)
  - [Doxygen](#linux-doxygen)
  - [Cmake](#linux-cmake-tool)
  - [json-c Library](#linux-json-c-library)
  - [Berekley DB Library](#linux-berkeley-db-library)
  - [JPEG library](#jpeg-library)
  - [gnuplot](#gnuplot)
  - [OpenCV](#opencv-library)
## Windows build tools <a id="windows-build-tools"/>
The following are Windows tools to install for building the system.
The software installation has been tested under Windows using Windows Subsystem for Linux
[WSL2](#windows-wsl2-linux) and [Pengwin](https://www.whitewaterfoundry.com/).
The following additional Windows tools may be installed.
- [Windows Terminal](#windows-terminal-tool) is a useful Windows command line interface for WSL2.
- [JetBrains CLion](#jetbrains-clion) is an optional C++ IDE.
### WSL2 Linux <a id="windows-wsl2-linux"/>
[WLS2](https://learn.microsoft.com/en-us/windows/wsl/) is a native Linux running under Windows 10/11.
These are instructions for installing [Windows WSL2](https://learn.microsoft.com/en-us/windows/wsl/install).
WSL2 has specific [hardware requirements](https://learn.microsoft.com/en-us/windows/wsl/troubleshooting?source=recommendations),
including a 64-bit processor with second-level address translation (SLAT) and at least 4GB of RAM. 
Most new Windows systems should be adequate.
The command to install WSL2 on Windows is:
```
$ wsl --install
```
After installing WSL2 a Linux distribution must be selected, in our case, Pengwin.

### WSL2 Pengwin Linux Distribution <a id="wsl2-pengwin-distribution"/>
THe WSL2 [Pengwin](https://www.whitewaterfoundry.com/) Windows distribution
which may be obtained from the 
[Microsoft Store](https://www.microsoft.com/store/apps/9NV1GV1PXZ6P?cid=storebadge&ocid=badge) 
for a nominal cost.
The current version of [Ubuntu](https://ubuntu.com/tutorials/install-ubuntu-on-wsl2-on-windows-10#1-overview)
22.04 is not a current enough version of Linux to build the system and is not supported.
Other Linux versions such as MacOS and Centos are not supported.
- ths command`lets you setup some 
[settings and tools](https://www.youtube.com/watch?v=xpo1MFARIzo) for pengwin:
```
$ pengwin-setup
```
### Windows Terminal <a id="windows-terminal-tool"/>
Windows Terminal is a useful Windows tool to develop WSL2 Linux applications and
may be obtained from the Microsoft Store for free.
Microsoft has a [tutorial](https://learn.microsoft.com/en-us/windows/terminal/install) for starting with Windows Terminal.
Scott Hanselman has an excellent [video](https://www.youtube.com/watch?v=FC-gLkYWXLw) on using Windows Terminal.

### JetBrains CLion <a id="jetbrains-clion"/>
[JetBrains CLion](https://www.jetbrains.com/clion) is an optional Windows C++ IDE.
It requires buying a license if not for a student or teacher.

- run the following commands in [Pengwin Linux](https://github.com/WhitewaterFoundry/Pengwin/issues/581) before installing CLion:
```
$ pengwin-setup install PROGRAMMING C++
$ pengwin-setup install PROGRAMMING JETBRAINS
```
- [download](https://www.jetbrains.com/clion/download/#section=windows) and install Jetbrains CLion
- set up CLion to run with Windows WSL2 Linux using these [instructions](https://www.jetbrains.com/help/clion/how-to-use-wsl-development-environment-in-product.html),

`cv-workbench`is written in C++ and builds using Cmake.
JetBrains has a [tutorial](https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html) on setting up CLion for a Cmake project.
Do not install Cmake for Windows as it may interfere with the Linux Cmake build.

## Linux Build Tools and C++ libraries <a id="linux-build-tools-and c++-libraries"/>
There are several Linux tools and C++ libraries required for the build.
Pengwin Linux uses the`apt`command to install many Linux library and tool packages:
```
$ sudo apt update
$ sudo apt install <package>
```
Always run`apt update`before`install`.
Some packages are not available under`apt`, or have`apt`packages
versions that are too old to use.
In those cases, they can be directly downloaded from a web site or built from source.

### Linux compiler tools <a id="linux-compiler-tools"/>
The Linux`build-essential`package installs the C++ compiler,
debugger, libraries, other development tools required for the build.
`build-essential`includes:
- [g++, gcc](https://gcc.gnu.org/)
- [make](https://www.gnu.org/software/make/)  
Some other Linux build tools are also included.
They are installed with:
```
$ sudo apt-get update
$ sudo apt install build-essential libncurses-dev libbsd-dev
```

### Git <a id="linux-git-tool"/>
Linux [git](https://git-scm.com/) is required for the build.
It can be installed with this command:
```
$ sudo apt-get update
$ sudo apt install git
```
### pthreads Library <a id="linux-pthreads-library"/>
Linux`pthreads`is a C++ threading library is required for the build.
```
$ sudo apt-get update
$ sudo apt install libpthread-stubs0-dev
```
### OpenSSL Library <a id="linux-openssl-library"/>
Linux [OpenSSL](https://www.openssl.org/) is a secure communications C++ library required for the build.
It can be [installed](https://learnubuntu.com/install-openssl/) these instructions:
```
$ sudo apt-get update
$ sudo apt install libssl-dev openssl
```
### Doxygen <a id="linux-doxygen"/>
Doxygen generates [Javadoc](https://www.oracle.com/technical-resources/articles/java/javadoc-tool.html)-like html files from C++ source code.
It can be installed with these [instructions](https://www.tutorialspoint.com/how-to-install-doxygen-on-ubuntu):
```
$ sudo apt-get install doxygen opt graphviz mscgen dia
```
### Cmake <a id="linux-cmake-tool"/>
[Cmake](https://cmake.org/) is required for building`cv-workbench` and some C++ iibraries that must be built from source.
The CMake website has a nice [totorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
for creating a Cmake project.
The basic Linux version can be installed with this command:
```
$ sudo apt-get update
$ sudo apt install cmake
```
Building the [JPEG library](#jpeg-library) from source, 
below, will require the a `cmake` version 3.29 or later.
The default`apt` version may not be recent enough.
If so, `cmake`must be built from the latest source.
The `cmake` version can be checked with this command:
```
$ cmake --version
cmake version 3.25.1
```
Building the JPEG library with an `apt` version before 3.29  will produce a
[CMP0159](https://manpages.debian.org/unstable/cmake-data/cmake-policies.7.en.html) error.

To build`cmake` from source,
sownload the latest source from the`Unix/Linux Source` link on the [download website](https://cmake.org/download/),
e.g.,`cmake-3.31.1.tar.gz`.
[Build](https://cmake.org/cmake/help/book/mastering-cmake/chapter/Getting%20Started.html#getting-and-installing-cmake-on-your-computer) it with these instructions:
```
$ tar xvf cmake-3.31.1.tar.gz
$ cd cmake-3.31.1
$ mkdir build
$ cd build
$ ../bootstrap 
$ sudo make install
```
Cmake requires an additional tool be installed,`pkg-config`:
```
$ sudo apt-get update
$ sudo apt install pkg-config
```
### json-c Library <a id="linux-json-c-library"/>
[json-c](https://github.com/json-c/json-c) is a C-based JSON manipulation library.
The following will download the latest version of`json-c`from the git repository and [build](https://github.com/json-c/json-c/blob/master/README.md)
static libraries and install them in`/usr/local`:
```
$ git clone git@github.com:json-c/json-c.git
$ mkdir json-c-build
$ cd json-c-build
$ cmake ../json-c 
$ cmake --build .
$ sudo cmake --install . 
```
[Install](https://learn.microsoft.com/en-us/vcpkg/users/buildsystems/cmake-integration) in Windows with [this](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vs?pivots=shell-powershell)
and [this](https://github.com/json-c/json-c/blob/master/README.md):
```
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg; .\bootstrap-vcpkg.bat
vcpkg integrate install
vcpkg install json-c
```
### Berekley DB Library <a id="linux-berkeley-db-library"/>
The [Berkeley DB](https://www.oracle.com/database/technologies/related/berkeleydb.html) library
is an efficient, embedded non-SQL key-indexed database used by`cv-workbench` for image storage.
The latest version is required and can be built from source.
- download the latest version of the [source](https://www.oracle.com/database/technologies/related/berkeleydb-downloads.html).
- select the latest Berkeley DB *version* Download link. You may need to create an Oracle account.
- select the`Linux x86-64 platform`, accept the license agreement, and select`Download`.
- run the downloaded Windows executable named Oracle_SSN_DLM_*nnn*.exe to create a file named V*nnnnnn-nn*.zip.
- select Open Destination from the opened window to find the zip.
- right-click/drag the zip using File Explorer and select Expand into a directory named V*nnnnnn-nn*.
- the build requires these Linux development tools:
  - [autoconf](https://askubuntu.com/questions/290194/how-to-install-autoconf)
  - [libtool](https://www.gnu.org/software/make/)
  - [libdb5.3-dev](https://launchpad.net/ubuntu/jammy/+package/libdb5.3++-dev)
- Install these with:
```
$ sudo apt-get update
$ sudo apt-get install autoconf
$ sudo apt-get install libtool
$ sudo apt install libdb5.3-dev
```
- build using these [instructions](https://docs.oracle.com/cd/E17276_01/html/installation/build_unix.html).

To build, let`BDB_HOME`be the Berkeley DB installation directory, e.g.,V*nnnnnn-nn*/db-18.1.40.
There are some other`configure` arguments described in these files:
- `$BDB_HOME/docs/installation/build_unix_conf.html`
- `$BDB_HOME/docs/installation/build_unix_flags.html`
 
Useful ones include:
- `--prefix=`*directory* determines the final installation directory, default is`/usr/local`
- `--enable-cxx`to build the C++ library
- `--disable-shared`is useful to build with static rather than dynamic libraries
- `--enable-debug` to build the library for debugging
- `CC=`*c compiler* is the C compiler to use, e.g.,`cc`or`gcc`, default is`gcc`
- `CFLAGS=`*flags* are the C compiler flags
- `CXXFLAGS=`*flags* are the C++ compiler flags

A good set of commands to [build Berkeley DB](https://github.com/SerenadeEXE/BerkeleyDBTutorial)
to install C++ and C static libraries under`/usr/local`are:
```
$ cd $BDB_HOME/build_unix
$ LDFLAGS="-R/usr/lib/x86_64-linux-gnu"
$ ../dist/configure --prefix=/usr --enable-cxx 
$ make
$ sudo make install
```
### JPEG library <a id="jpeg-library"/>
Install the [Independent JPEG Group](http://www.ijg.org/) `jpeg-9e` library
from [source](http://www.ijg.org/files/)
(also from [github](https://github.com/LuaDist/libjpeg)).
- See the source [documentation](http://www.ijg.org/files/README).
- There is a [wiki](https://jpegclub.org/) and more [documentation](https://en.wikipedia.org/wiki/Libjpeg).
- See the JPEG [documentation](https://jpegclub.org/reference/reference-sources/).
- There is an `example.c` file in the source that is an example of using the library.
- Compile `jpeg-9e` C source files with the `jpeglib.h` include file and link with `-ljpeg`.

Install the C static libraries under`/usr/local`with:
```
$ ./configure
$ make
$ make test
$ sudo make install
```

### gnuplot <a id="gnuplot"/>
`gnuplot` plots data from the histogram operation. 
- download the file *version*`/gp602-win64-mingw.zip` from the
[gnuplot download site](https://sourceforge.net/projects/gnuplot/files/gnuplot/)
- unpack the archive into a directory
- add the `gnuplot/bin` directory to the `PATH` environment variable

### OpenCV <a id="opencv-library"/>
Optionally install the [OpenCV](https://docs.opencv.org/)
open source computer vision package to develop workbench applications with OpenCV.
- install OpenCV with these [instructions](https://docs.opencv.org/4.5.3/d7/d9f/tutorial_linux_install.html)
  )
- See the OpenCV [documentation]()
- Compile OpenCV C++ source files with the `opencv2/opencv.hpp` include file
and add the libraries to the `CMakeFiles.txt` file



