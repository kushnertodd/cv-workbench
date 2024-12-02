# cv-workbench build tools and libraries installation <a id="build-tools-and-libraries-installation"/>
These are instruction to build `cv-workbench` for Linux.

# Table of Contents
- [Linux development tools and libraries](#linux-development)
  - [Linux C++ Development Tools](#linux-c++-development-tools)
    - [JetBrains CLion](#jetbrains-clion)
    - [WSL2 Linux distribution for Windows 10](#windows-10-wsl2-linux-distributions)
    - [Windows Terminal](#windows-terminal-tool)
    - [Linux Build Tools](#linux-build-tools)
    - [Git](#linux-git-tool)
    - [Cmake](#linux-cmake-tool)
  - [Linux C++ Libraries](#linux-c++-libraries)
    - [pthreads Library](#linux-pthreads-library)
    - [OpenSSL Library](#linux-openssl-library)
    - [Doxygen](#linux-doxygen)
    - [json-c Library](#linux-json-c-library)
    - [Berekley DB Library](#linux-berkeley-db-library)
    - [JPEG library](#jpeg-library)
    - [OpenCV](#opencv-library)
    - [ESP32-CAM](#esp32-cam)
## Installation
These are instructions to build CV Workbench from source. 
Below are requirements to set up the system to build and run.
Once they are in place, the system may be built with:

```
$ sh build.sh
```
This builds the main program `cv-workbench` and some additional utilities.

The software is assumed to run under Linux [Ubuntu](https://ubuntu.com/) or compatible Linux version,
such as Microsoft WSL2 [Pengwin](https://www.whitewaterfoundry.com/).
The following Linux modules need to be installed.

# Linux development tools and libraries <a id="linux-development"/>
These are instructions to prepare the Linux build environment.

## Linux C++ Development Tools <a id="linux-c++-development-tools"/>
Linux development tools include:
- JetBrains CLion
- WSL2 Linux distribution for Windows 10
- Windows Terminal
- Linux Build Tools
- Git
- Cmake

### JetBrains CLion <a id="jetbrains-clion"/>
[JetBrains CLion](https://www.jetbrains.com/clion/download/#section=windows) is a free C++ IDE.
The Berekeley DB C++ Framework is a Cmake project.
JetBrains has a
[tutorial](https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html)
on setting up CLion for a Cmake project.

- install CLion from jetbrains, buy license
- install Windows [CMake](https://cmake.org/download/)
- install Perl from activastate.com

### WSL2 Linux distribution for Windows 10 <a id="windows-10-wsl2-linux-distributions"/>
WSL2 is a native Linux running under Windows 10.
These are instructions for installing [Windows 10 WSL2](https://learn.microsoft.com/en-us/windows/wsl/).
WSL2 has specific [hardware requirements](https://learn.microsoft.com/en-us/windows/wsl/troubleshooting?source=recommendations),
including a 64-bit processor with second-level address translation (SLAT) and at least 4GB of RAM. Any new Intel Windows system should be adequate.
The command to [install](https://learn.microsoft.com/en-us/windows/wsl/install) WSL2 on Windows 10 is:
```
$ wsl --install
```
The install instructions are currently for Pengwin or Ubuntu.
The Linux build is currently tested on Windows 10 WSL2 with [Pengwin](https://www.whitewaterfoundry.com/),

#### Linux Distributions
Linux development was done under Windows 10 WSL2 with [Pengwin](https://www.whitewaterfoundry.com/),
which may be obtained from the Microsoft Store.
[Ubuntu](https://ubuntu.com/tutorials/install-ubuntu-on-wsl2-on-windows-10#1-overview)
may also be obtained from the Microsoft Store.
The instructions likely work for other types of Linux,
such as CentOS,
or other types of Unix,
such as MacOS, possibly with modifications.
These are [instructions](https://learn.microsoft.com/en-us/windows/wsl/use-custom-distro)
for installing other WSL2 Linux distributions.

### Windows Terminal <a id="windows-terminal-tool"/>
You likely would like to use [Windows Terminal](https://aka.ms/terminal)
to develop using WSL2 Linux.
Windows Terminal may be obtained from the Microsoft Store.
This is a Microsoft [tutorial](https://learn.microsoft.com/en-us/windows/terminal/install) for starting with Windows Terminal.
Scott Hanselman has an excellent [video](https://www.youtube.com/watch?v=FC-gLkYWXLw) on using Windows Terminal.

### Linux Build Tools <a id="linux-build-tools"/>
There are several Linux C++ libraries and tools required for the build.
Pengwin and Ubuntu use the`apt`command to install many Linux library and tool packages:
```
$ sudo apt update
$ sudo apt install <package>
```
Always run`apt update`before`install`.
Some packages are not available under`apt`, or some`apt`packages
have versions that are too old to use.
In those cases, they can be directly downloaded from a web site or built from source.

The Linux`build-essentials`package installs the C++ compiler,
debugger, libraries, other development tools required for the build.
`build-essential`includes:
- [g++, gcc](https://gcc.gnu.org/)
- [make](https://www.gnu.org/software/make/)  
  They are installed with:
```
$ sudo apt-get update
$ sudo apt install build-essential
```

### Git <a id="linux-git-tool"/>
[git](https://git-scm.com/) is required for the build.
It can be installed with this command:
```
$ sudo apt-get update
$ sudo apt install git
```
### Cmake <a id="linux-cmake-tool"/>
Berkeley DB C++ Framework is written in C++.
[Cmake](https://cmake.org/) is used for building C++ applications.
The CMake website has a nice [totorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
for learning it.
It can be installed with this command:
```
$ sudo apt-get update
$ sudo apt install cmake
```
In the unlikely case that the version available from`apt`is too old to use.
If so, it must be built from source.
Select the latest source from the`Unix/Linux Source`link on the [download website](https://cmake.org/download/),
e.g.,`cmake-3.31.1.tar.gz`,
and [build](https://cmake.org/install/) with these instructions:
```
$ gunzip -c cmake-3.31.1.tar.gz | tar xvf -
$ cd cmake-3.31.1
$ ./configure --prefix=/usr
$ sudo make install
```
Cmake requires an additional tool be installed,`pkg-config`:
```
$ sudo apt-get update
$ sudo apt install pkg-config
```
## Linux C++ Libraries <a id="linux-c++-libraries"/>
Various C++ libraries are required for the Linux build.
### pthreads Library <a id="linux-pthreads-library"/>
Linux`pthreads`is a C++ threading library is required for the build.
It should already be installed in Linux.
In the event it is not, it can be installed with this command:
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
Doxygen generates Javadoc-like html files from C++ source code.
It can be installed with these [instructions](https://www.tutorialspoint.com/how-to-install-doxygen-on-ubuntu):
```
$ sudo apt-get install doxygen opt graphviz 
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
### Berekley DB Library <a id="linux-berkeley-db-library"/>
The [Berkeley DB](https://www.oracle.com/database/technologies/related/berkeleydb.html) library
is an efficient, embedded non-SQL key-indexed database.
The latest version is required and can be built from source.
Download source for the latest version from:  
https://www.oracle.com/database/technologies/related/berkeleydb-downloads.html
- Select from the Berkeley DB *version* link. You may need to create an Oracle account.
- Select the`Linux x86-64 platform,`read accept the license agreement, and select`Download`.
- Run the downloaded Windows executable named Oracle_SSN_DLM_*nnn*.exe to create a file named V*nnnnnn-nn*.zip.
- Select Open Destination from the opened window to find the zip.
- Right-click/drag the zip using File Explorer and select Expand into a directory named V*nnnnnn-nn*.

Build using these [instructions](https://docs.oracle.com/cd/E17276_01/html/installation/build_unix.html).
- In Linux, first install`autoconf`and other required development tools:
  - [autoconf](https://askubuntu.com/questions/290194/how-to-install-autoconf)
  - [libtool](https://www.gnu.org/software/make/)
  - [libdb5.3-dev](https://launchpad.net/ubuntu/jammy/+package/libdb5.3++-dev)
  - [libssl-dev](https://launchpad.net/ubuntu/bionic/+package/libssl-dev)

Install these with:
```
$ sudo apt-get update
$ sudo apt-get install autoconf
$ sudo apt-get install libtool
$ sudo apt install libdb5.3-dev
```
To build, let BDB_HOME be the Berkeley DB installation directory, e.g.,V*nnnnnn-nn*/db-18.1.40.
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

### OpenCV <a id="opencv-library"/>
Install the [OpenCV](https://docs.opencv.org/4.5.3/d7/d9f/tutorial_linux_install.html)
open source computer vision package to develop workbench applications with [OpenCV](https://opencv.org).
- See the OpenCV [documentation](https://docs.opencv.org/).
- Compile OpenCV C++ source files with the `opencv2/opencv.hpp` include file
  and link with various `-lopencv_*` libraries found in `/usr/local/lib`.


