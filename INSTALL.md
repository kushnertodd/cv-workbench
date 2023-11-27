# Installation
These are instructions for installing CV Workbench.
They include:
- Downloading the CV Workench Github repository.
- Setting up Windows 10 to run Linux.  
- Running the CV Workbench program tests to verify the installation  

Setting up MacOS will not be discussed here, but MacOS comes with Linux installed.

## Downloading the CV Workbench Github repository
The steps to download CV Workbench on Windows 10 are the following.

### Install Git for Windows
Download [git for Windows](https://git-scm.com/download/win) and install it.

### Download the repository
From a command prompt, first go to the directory in which you want to install CV Workbench.
Then run this command:
```
C:\>git clone https://github.com/kushnertodd/cv-workbench.git
```

## Setting up Windows 10 to run Linux

The first steps to installing Linux on Windows is to install
[Windows Subsystem for Linux WSL2](https://docs.microsoft.com/en-us/windows/wsl/install).
Follow those instructions which begin with running this command from an administrator
command prompt and restarting:
```
C:>wsl --install
```
This will install Linux [Ubuntu](https://ubuntu.com/). You can also install a
compatible Linux version such as [Pengwin](https://www.whitewaterfoundry.com/)
from Microsoft Store.
You may also want to install Windows Terminal from the Microsoft Store
to run Linux.
You may wish to read up on 
[Linux](https://www.digitalocean.com/community/tutorials/an-introduction-to-linux-basics)
first if you are new to it.

## Running CV Workbench from Linux
Start Linux by opening Ubuntu from the Start Menu. 
Change to the directory in which CV Workbench was installed.
If CV Workbench was installed in the directory cv-workbench
under your Windows home directory, run:
```
$ cd /mnt/c/Users/user-name/cv-workbench
```
where 'user-name' is your Windows user name.

Run the following commands to test the CV Workbench installation:
```
$ cd src
$ ../bin/cv-workbench test/filter-edge-sobel/square45-90_gray-sobel-0.json
```
Test that the expected output images were produced:
```
$ cd src/images
$ ls
square45-90_gray-sobel-0.bin  square45-90_gray-sobel-0.jpg
```
Open `square45-90_gray-sobel-0.jpg` in File Explorer and verify that it looks like this:  
<img src="src/images/square45-90_gray-sobel-0.jpg">
If so, your installation is successful.

# Building CV Workbench from suorce
To build custom C++ operators, the Linux build environment must be configured. 
The following Linux modules need to be installed.
Building from C++ requires g++ version 10.
[Pengwin](https://www.whitewaterfoundry.com/) installs version 10
by default in the install step below
but Ubuntu installs version 9 which will not build properly.
At this time, Pengwin is required to build custom operators.

### make
Install the `make` build utility with:
```
$ sudo apt install make
```
### gcc and g++
Install the `gcc` and `g++` build utilities with:
```
$ sudo apt install build-essential
```
### Json-c
Install the Json-c C/C++ Json parsing library under Linux with:
```
sudo apt install libjson-c-dev
```
[comment]: <> (or sudo apt-get install libjson0 libjson0-dev)

- It can be cloned and built from [source](https://github.com/json-c/json-c) (cv-workbench was developed using this).
- See the json-c [documentation](https://json-c.github.io/json-c/)
  and [reference](https://json-c.github.io/json-c/).
- See the json-c [tutorial and examples](https://linuxprograms.wordpress.com/category/json-c).
- See an additional [tutorial](https://github.com/rbtylee/tutorial-jsonc)
  with these [examples](https://github.com/rbtylee/tutorial-jsonc/blob/master/tutorial/index.md).
- See JSON [documentation](https://www.json.org/json-en.html) at [json.org](https://www.json.org/json-en.html).
- JSON can be formatted on a [website](https://jsonformatter.org/),
  with the [jq](https://stedolan.github.io/jq/download/) command-line app,
  or in some IDEs such as [notepad++](https://notepad-plus-plus.org/) or JetBrains [Clion](https://www.jetbrains.com/clion/).
- Compile jcson-c C source files with the `json-c/json.h` include file
  and link with `-ljson-c`.

### JPEG support
Install the Independent JPEG Group version`jpeg-9e` or latest jpeglib library from source.
- See the source [documentation](http://www.ijg.org/files/README).
- There is a [wiki](https://jpegclub.org/) and more [documentation](https://en.wikipedia.org/wiki/Libjpeg).
- See the JPEG standard [documentation](https://jpegclub.org/reference/reference-sources/).
- There is an `example.c` file in the source that is an example of using the library.
- Compile `jpeg-9e` C source files with the `jpeglib.h` include file and link with `-ljpeg`.
- Download the source and build.
#### Linux build
- Download [jpegsrc.v9e.tar.gz](https://www.ijg.org/files/jpegsr9e.zip) and extract:  
```
$ gunzip jpegsrc.v9e.tar.gz
$ tar xvf jpegsrc.v9e.tar
```
- Follow the instructions in `jpeg-9e/install.txt` to install.
#### Windows build
- Download [https://www.ijg.org/files/jpegsr9e.zip](https://www.ijg.org/files/jpegsr9e.zip)  
```
$ unzip jpegsrc.v9e.zip
```
- Open `Visual Studio Develper Command Prompt (Tools|Command line|Developer Command Prompt`.
- Follow the instructions in `jpeg-9e/install.txt` to install,
e.g, for Microsoft Windows Visual Studio 2022 Version 17:
  - run  `C:\> nmake /f makefile.vs setup-v17`
  - open `jpeg.sln` in Visual Studio and build.
  - open `apps.sln` in Visual Studio and build.  
## Optional packages
These packages are not yet used by CV Workbench, but may be in the future.

### Berkeley DB
Install the Berkeley DB open source embedded database system from the zip
[source](https://www.oracle.com/database/technologies/related/berkeleydb-downloads.html)
with these [instructions](https://docs.oracle.com/cd/E17076_05/html/installation/index.html).
- See alternate install [instructions](https://cryptoandcoffee.com/mining-gems/install-berkeley-4-8-db-libs-on-ubuntu-16-04)
  for the freesource version.
- You make need to install these packages:
```
sudo apt install autoconf libtool
```
- See the Oracle Berkeley DB [documentation](https://docs.oracle.com/cd/E17276_01/html/programmer_reference/index.html).
- Other documentation is at [DZone](https://dzone.com/refcardz/getting-started-oracle)
- See Berkeley DB [tutorials](https://web.stanford.edu/class/cs276a/projects/docs/berkeleydb/reftoc.html)
  and [sample applications](https://www.oracle.com/database/technologies/related/berkeleydb.html).
- Compile Berkeley C source files with the `db.h` include file
  and link with `-ldb`.


### OpenCV
Install the [OpenCV](https://docs.opencv.org/4.5.3/d7/d9f/tutorial_linux_install.html)
open source computer vision package to develop workbench applications with [OpenCV](https://opencv.org).
- See the OpenCV [documentation](https://docs.opencv.org/).
- Compile OpenCV C++ source files with the `opencv2/opencv.hpp` include file
  and link with various `-lopencv_*` libraries found in `/usr/local/lib`.

### Sqlite3
Install the embedded relational database [Sqlite3](https://www.sqlite.org/) under Linux with:
```
sudo apt install sqlite3
```

- It can be built from [source](https://www.sqlite.org/2022/sqlite-amalgamation-3380500.zip).
- See these [build](https://www.sqlite.org/howtocompile.html) instructions.
- A Windows [ODBC driver](http://www.ch-werner.de/sqliteodbc/)
  can be installed for use by, e.g., Microsoft Access.
- See the sqlite3 [tutorial](https://www.sqlitetutorial.net/).
- See the [sqlite3](https://www.sqlite.org/docs.html) and
  [C/C++ API](https://sqlite.org/cintro.html) documentation
  with a [tutorial](https://www.sqlite.org/c_interface.html),
  an [example](https://sqlite.org/src/file/src/shell.c.in),
  and [source files](https://sqlite.org/src/file/src).
- Compile sqlite3 C source files with the `sqlite3.h` include file
  and link with the `sqlite3.o` file generated from the above
  [source](https://www.sqlite.org/2022/sqlite-amalgamation-3380500.zip)
  with:
```
gcc -c sqlite3.c
```
- See these examples of building apps with
  [sqlite3](https://www.devdungeon.com/content/compiling-sqlite3-c).

### ESP32-CAM
To use the Arduino ESP32-CAM for image input, install the Arduino
[ESP32-CAM module](https://www.edgoad.com/2021/02/programming-esp32cam-using-arduino-uno.html) in the [Arduino IDE](https://www.arduino.cc/en/software).
- See the ESP32-CAM camera webserver [still photo capture](https://github.com/kushnertodd/CameraWebServer-still) project.

