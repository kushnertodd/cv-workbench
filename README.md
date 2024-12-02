# CV-Workbench
 
This describes the Computer Vision Workbench, 
a software system that allows a non-programmer to do experimentation with image processing. 
Following are 

## Github repository

This is the Github repository for CV Workbench:

https://github.com/kushnertodd/cv-workbench

## Documentation

The documentation can be found in the Microsoft Word file:

`doc/cv-workbench.docx`

## Quick start

For a quick demonstration of the system, `cd` to `demo/` and follow the instructions in `demo/README.txt`.

## Installation

To build the system from source, follow the instructions in INSTALL.md.

## CV-Workbench programs

Linux executables for the CV Workbench programs can be found in here:

`bin/`

The programs delivered with CV Workbench are: 
```
cv-workbench   the main CV Workbench program
image-copy     copies JPEG images to and from internal binary format
image-dump     dumps a binary image as tab-delimited text
image-info     prints statistics of an image file 
jpegtran       converts color JPEG images to grayscale
```

### cv-workbench
This is the main CV Workbench program. It runs against a JSON script
containing image processing operators as described in the documentation. 
It's usage is:

`$ ./cv-workbench` *scriptfile*.json  

where *scriptfile* is the JSON image operator script.
After running it produces a log file as described in the documentation in:

*scriptfile*.log

### image-copy
This copies JPEG images to and from internal binary format.
It's usage is:

`$ ./image-dump` *in-filename* *out-filename*

where *in-filename* is an input JPEG or internal binary image file, with extensions
`.jpg` or `.bin`, and *out-filename* is the output converted image.
`image-dump` determines the format from the filename extension.

### image-dump in-filename

This dumps JPEG or internal binary format images as tab-delimited text.
It's usage is:

`$ ./image-dump` *in-filename*.*ext*

where *in-filename* is an input JPEG or internal binary image file and the extension *ext*
`.jpg` or `.bin`.
The tab-delimited output file is in *out-filename*`.txt`.

### image-info
This prints statistics of an image file, such as row/column size, number of
components (1 = grayscale, 3 = color), minimum and maximum values.
It's usage is:

`$ ./image-info` *in-filename*

### jpegtran       
This converts color JPEG images to grayscale. It's usage is:

`$ ./jpegtran -g ` *in-filename*`.jpg` `>`*out-filename*.`jpg`

where *in-filename*`.jpg` is the input color JPEG image file and
*out-filename*`.jpg` is the output grayscale JPEG image file.

## Tests

There are system tests in the `src/test` to run unit testing on cv-workbench.
The directories involved are:
```
src/tests           directories with unit tests for various image processing operators
src/test/reference  sample input images for tests
src/images          directory for test output images and data
```

There are two scripts that can be run in `src/test`:
```
$ sh test-run-dirs.sh         runs unit tests for all image processing operations
$ sh test-clean-dirs.sh       cleans all test images and data from src/images
```
There are scripts in each image processing operations directory, such as `src/test/filter-edge-kirsch`,
to run unit tests just for that operation. They are run with:
```
$ sh test-run-dir.sh         runs unit tests for the image processing operation
$ sh test-clean-dir.sh       cleans all unit test data out of src/images
```