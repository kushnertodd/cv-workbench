# Berkeley DB C++ Framework build tools and libraries installation <a id="build-tools-and-libraries-installation"/>
Berkeley DB C++ Framework may be built for Linux or Windows.
Instructions to build for these platforms follow.

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
- [Windows development tools and libraries installation](#windows-development)
  - [Windows C++ Development Tools](#windows-c++-development-tools)
    - [Visual Studio](#visual-studio-2022-development)
    - [Git](#windows-git-tool)
    - [Cmake](#windows-cmake-tool)
    - [vcpkg](#windows-vcpkg-tool)
  - [Windows C++ Libraries](#windows-c++-libraries)
    - [Berekley DB](#berekley-db-development)
    - [Json-c](#json-c-development)

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
$ sudo apt install build-essentials git
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
The build requires the latest version, currently 3.26.1.
The version available from`apt`is too old to use, so it must be built from source.
Select the latest source from the`Unix/Linux Source`link on the [download website](https://cmake.org/download/),
e.g.,`cmake-3.26.3.tar.gz`,
and [build](https://cmake.org/install/) with these instructions:
```
$ gunzip -c cmake-3.26.3.tar.gz | tar xvf -
$ cd cmake-3.26.3
$ ./configure --prefix=/usr
$ make
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
$ sudo apt install openssl
```
### Doxygen <a id="linux-doxygen"/>
Doxygen generates Javadoc-like html files from C++ source code. 
It can be installed with these [instructions](https://www.tutorialspoint.com/how-to-install-doxygen-on-ubuntu):
```
$ sudo apt-get doxygen
$ sudo apt-get opt
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

[Build](https://docs.oracle.com/cd/E17276_01/html/installation/build_unix.html) using these instructions.
- In Linux, first install`autoconf`and other required development tools:
  - [autoconf](https://askubuntu.com/questions/290194/how-to-install-autoconf)
  - [libtool](https://www.gnu.org/software/make/)
  - [libssl-dev](https://packages.ubuntu.com/bionic/libssl-dev)
  - [libdb5.3-dev](https://packages.ubuntu.com/bionic/libdb-dev)

Install these with:
```
$ sudo apt-get update
$ sudo apt-get install autoconf
$ sudo apt-get install libtool
$ sudo apt install libssl-dev
$ sudo apt install libdb5.3-dev
```
To build, let BDB_HOME be the Berkeley DB installation directory, e.g.,V*nnnnnn-nn*/db-18.1.40:
```
$ cd $BDB_HOME/build_unix
$ ../dist/configure --prefix=/usr --enable-cxx 
$ make
$ sudo make install
```
There are some other`configure` arguments described in these files:  
- `$BDB_HOME/docs/installation/build_unix_conf.html`  
- `$BDB_HOME/docs/installation/build_unix_flags.html` 

# Windows development tools and libraries installation <a id="windows-development"/>
- Windows development was done under Windows 10
  - Windows 11 is claimed compatible but is reportedly bloatware

## Windows C++ Development Tools <a id="windows-c++-development-tools"/>
Following are Windows tools used for development. 

### Visual Studio 2022 <a id="visual-studio-2022-development"/>
This is the Windows C++ development environment used.
#### Required Visual Studio components
This section includes Visual Studio components required to build the project.
- Download [Visual Studio 2022 Community](https://visualstudio.microsoft.com/vs/community/)
- Select the following Modules:
    - .NET desktop development
    - Desktop development with C++
    - Universal Windows Platform development
- Select the following Individual Component:
    - Class Designer
- Install the following extensions:
    - Select Extensions->Manage Extensions
    - Install these extensions
        - Search for`markdown`and select`Markdown editor (64-bit)`
        - Search for`json`and select`Json formatter`
        - Search for 'doxygen' and select 'Doxygen Comments' by Finn Gegenmantel
    - Restart Visual Studio

### Git <a id="windows-git-tool"/>
Download and run the 64-bit Git for Windows installer
from the [Git download website](https://git-scm.com/download/win).
### Cmake <a id="windows-cmake-tool"/>
Berkeley DB C++ Framework is written in C++. 
[Cmake](https://cmake.org/) is used for building C++ applications.
The build requires the latest version, currently 3.26.1.
Select the latest Windows version from the`Windows x64 Installer`
link on the [download website](https://cmake.org/download/),
e.g.,`cmake-3.26.3-windows-x86_64.msi`, and run the installer.

### vcpkg <a id="windows-vcpkg-tool"/>
`vcpkg`is useful to install Windows tools without building them from source.
Instructions to install`vcpkg`are:
```
C:>git clone https://github.com/microsoft/vcpkg
C:>vcpkg
C:>bootstrap-vcpkg.bat
```
(Optional) If using with Visual Studio run:
```
C:>vcpkg integrate install
```
## Windows C++ Libraries <a id="windows-c++-libraries"/>
Various C++ libraries are required for the Linux build.
### Berekley DB <a id="windows-berekley-db-development"/>
Berkeley DB is an efficient, embedded non-SQL key-indexed database.
#### Download
The latest Berkeley DB version can be downloaded from:
- https://www.oracle.com/database/technologies/related/berkeleydb-downloads.html
- Select the`Download`link under 'Berkeley DB *version*', e.g.,`Berkeley DB 18.1 (18.1.40)`
  - You may need to create an Oracle account. 
- On the next screen:
  - Check next to 'Oracle Berkeley DB *version*', e.g.,`Oracle Berkeley DB 18.1.401`
  - Select Platform`Linux x86-64`
  - Accept the license agreements
  - Select`Download`
- It will download a Windows executable named like 'Oracle_SSN_DLM_*nnn*.exe'
- Run the executable, it will create a file named, e.g.,`V997917-01.zip`.
- Select`Open Destination`from the window that appears to find the zip.
- Right-click the zip in File Explorer and select`Extract All...`into a directory, e.g.,`V997917-01`.

Let`BDB_HOME`be the Berkeley DB installation directory inside the directory above, e.g.,`db-18.1.40`.

- Linux installation
These are instructions to build [Berkeley DB for UNIX/POSIX](https://docs.oracle.com/cd/E17276_01/html/installation/build_unix.html)
- In Linux, first install the following tools, including`autoconf`and`libtool`:
    - [autoconf](https://askubuntu.com/questions/290194/how-to-install-autoconf)
    - [libtool](https://www.gnu.org/software/make/)
    - [libdb5.3-dev](https://packages.ubuntu.com/bionic/libdb-dev)
    - [libssl-dev](https://packages.ubuntu.com/bionic/libssl-dev)
```
$ sudo apt update
$ sudo apt install autoconf
$ sudo apt install libtool
$ sudo apt install libssl-dev
$ sudo apt install libdb5.3-dev
```
Instructions to build are:
```
$ cd $BDB_HOME/build_unix
$ ../dist/configure <arguments>
$ make
$ sudo make install
```
`configure`takes a few arguments.
They are described at these files:
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
### Windows installation
These are instructions to build [Berkeley DB for Windows](https://docs.oracle.com/cd/E17076_05/html/installation/build_win.html)
- Choose File -> Open -> Project/Solution.... and select the [file](https://docs.oracle.com/cd/E17076_05/html/installation/build_win.html#win_build32)
`%BDB_HOME%\build_windows\BDB_dotNet_vs2015.sln`
- Choose the desired project configuration from the drop-down menu on the tool bar (either Debug or Release).
- Choose the desired platform configuration from the drop-down menu on the tool bar (usually Win32 or x64).
- To build, right-click on the Berkeley_DB_vs2015 solution and select Build Solution.
- The library files are in`%BDB_HOME%\build_windows\x64\Debug`:
    - libdb181d.dll
    - libdb181d.lib
- The include files are in`%BDB_HOME%`

### Json-c <a id="windows-json-c-development"/>
You may install`jcon-c`from source or load it using`vcpkg`.
[json-c](https://github.com/json-c/json-c) <a id="json-c-development"/>
json-c is a C-based JSON manipulation library.
#### Download
json-c can be downloaded by cloning the git repository:
```
$ git clone git@github.com:json-c/json-c.git
```
Let JSONC_HOME be the json-c installation directory.

#### Building from source
Steps to building on Windows are to . 
- Run these command in the Visual Studio command window using Tools->Command Line->Developer Command Prompt
```
$ cd %JSONC_HOME%
$ mkdir build
$ cd build
$ cmake ..
```
- open the solution`build/json-c.sln`in Visual Studio and build solution
- library files are in`json-c/build/Debug`:
  - json-c-static.lib
  - json-c.lib
- include files are in`json-c`and`json-c/build`
#### Installing`json-c`using`vcpkg`
The command to install`json-c`using`vcpkg`are:
```
C:>vcpkg  install json-c
```

The`examples`directory has some C examples and instructions in`examples/README`.allation <a id="Windows-build-tools-and-libraries"/>
These are instructions to prepare the Windows build environment.
- [json-c](https://github.com/json-c/json-c) <a id="json-c-development"/>
json-c is a C-based JSON manipulation library.
- Download
json-c can be downloaded by cloning the git repository:
```
$ git clone git@github.com:json-c/json-c.git
```
Let JSONC_HOME be the json-c installation directory.
- Installing`json-c`from source
Steps to building on Windows from source are:
- Run these command in the Visual Studio command window using Tools->Command Line->Developer Command Prompt
```
$ cd %JSONC_HOME%_
$ mkdir build
$ cd build
$ cmake ..
```
- open the solution`build/json-c.sln`in Visual Studio and build solution
- library files are in`json-c/build/Debug`:
    - json-c-static.lib
    - json-c.lib
- include files are in`json-c`and`json-c/build`



















