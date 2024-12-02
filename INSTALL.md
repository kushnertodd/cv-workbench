## Installation
These are instructions to build CV Workbench from source. 
Below are requirements to set up the system to build and run.
Once they are in place, the system may be built with:

```
$ cd src
$ make
```
This builds the main program `cv-workbench` and some additional utilities.

The software is assumed to run under Linux [Ubuntu](https://ubuntu.com/) or compatible Linux version,
such as Microsoft WSL2 [Pengwin](https://www.whitewaterfoundry.com/).
The following Linux modules need to be installed.

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
or
```
sudo apt-get install libjson0 libjson0-dev
```

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

### Berkeley DB
Install the [Berkeley DB](https://docs.oracle.com/database/bdb181/index.html) open source embedded database system from the zip
[source](https://www.oracle.com/database/technologies/related/berkeleydb-downloads.html)
with these [instructions](https://docs.oracle.com/database/bdb181/html/installation/introduction.html).
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

### JPEG support
Install the [Independent JPEG Group](http://www.ijg.org/) `jpeg-9e` library
from [source](http://www.ijg.org/files/)
(also from [github](https://github.com/LuaDist/libjpeg)).
- See the source [documentation](http://www.ijg.org/files/README).
- There is a [wiki](https://jpegclub.org/) and more [documentation](https://en.wikipedia.org/wiki/Libjpeg).
- See the JPEG [documentation](https://jpegclub.org/reference/reference-sources/).
- There is an `example.c` file in the source that is an example of using the library.
- Compile `jpeg-9e` C source files with the `jpeglib.h` include file and link with `-ljpeg`.

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

