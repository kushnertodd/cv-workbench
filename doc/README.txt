CV Workbench demonstration

CV Workbench

cv-workbench v0.2.docx

The CV-Workbench is a framework to perform reproducible computer vision experiments. 
Users define experiment steps and store them allowing experiments to easily be reproduced.
An experiment management module guides runs image processing operations.
Image processing modules run with the specified input images and parameters.
Output images and data are stored on completion with experiment results including notes and explanations.
Experiments can be shared between CV-Workbench instances installed on different machines.

In this directory find a demonstration of basic CV Workbench capabilities. These are instructions for performing some basic image processing operations with CV Workbench.

Prerequisites

- CV Workbench currently runs under Linux. Have an Ubuntu compatible Linux system to run this demonstration.
- Windows or Mac OS are needed to view that document and various other files.
- CV-workbench v<version>.docx is a Microsoft Word document describing CV Workbench.


1. Instructions

- Copy the contents of this folder to a directory on Linux. Run these various demonstrations. 
- View the starting input image test/reference/square45-90_gray.jpg, which consistes of two squares, one horizontal and one rotated to 45 degrees.
- In Linux, cd to the folder in which you copied the files.

2. Sobel edge detector

The Sobel edge detector will compute the difference of each image pixel and its neighbors, producing an edge for every pixel at the edge of the shapes. Pixels within the shapes and the background will have no value because there is no difference in pixel values between the first pixel and its neighbors. These edge pixels will be used in the second step.

- Run this command. test-filter-edge-sobel-0-degrees.json is the JSON CV Workbench script used to produce the output images. The format is described in the document.

./cv-workbench test-filter-edge-sobel-0-degrees.json

- This command will run the Sobel edge detector and produce two files that are the result of applying the Sobel edge detector to square45-90_gray.jpg. View images/square45-90_gray_sobel_0_degrees.jpg to see how the Sobel creates an image of the edges of squares in the input file.

images/square45-90_gray_sobel_0_degrees.bin
images/square45-90_gray_sobel_0_degrees.jpg

3. Hough line detector

The Hough line detector will find edge pixels that lie on a common line. It does this brute force by passing lines in all angles through a pixel and keeping track of those lines. It then finds lines at all angles passing through another points, tracking those lines and noting which lines on which both of those points lie. Every two points will have one line passing through them. The process is repeated for other points, and by chance multiple points may lie on the same line. The lines with the most points are found as candidate lines in the image.

- Run this command:

./cv-workbench test/hough-draw-lines/test-hough-draw-lines-0-degrees-jpeg.json

- This command will run the Hough line detector, find the lines with the most common points, and create images with those lines superimposed on the edge image above. View these images in the images/ directory to see each line detected by the Hough operator.

square45-90_gray_sobel_0_degrees_line_0_-162.jpg
square45-90_gray_sobel_0_degrees_line_0_3.jpg
square45-90_gray_sobel_0_degrees_line_15_-156.jpg
square45-90_gray_sobel_0_degrees_line_15_-76.jpg
square45-90_gray_sobel_0_degrees_line_45_295.jpg
square45-90_gray_sobel_0_degrees_line_45_458.jpg
square45-90_gray_sobel_90_degrees_line_0_-162.jpg
square45-90_gray_sobel_90_degrees_line_0_3.jpg
square45-90_gray_sobel_90_degrees_line_15_-156.jpg
square45-90_gray_sobel_90_degrees_line_15_-76.jpg
square45-90_gray_sobel_90_degrees_line_45_295.jpg
square45-90_gray_sobel_90_degrees_line_45_458.jpg

- The Hough represents the lines in (angle, distance) polar coordinates. Wikipedia explains polar coordinates at the link below. The last two numbers at the end of each filename are the polar (angle, distance) coordinates of the drawn line.

https://en.wikipedia.org/wiki/Polar_coordinate_system

4. Conclusion

This demonstration shows CV Workbench applying the Sobel edge detector to find edges in the input image, then use the Hough edge detector in the resulting edge image. For those who wish to skip running the actual CV Workench program, samples of these output images for viewing can be found in the test/samples directory.

Many other operators are available in CV Workbench. When the first official version is released, a package containing the CV Workbench program and many examples of using those operators. Those examples can be used to as guides to create new CV Workbench JSON scripts. Send your email to todd.kushner@toddkushnerllc.com to put yourself on a mailing list to receive the notification that the first release is available and where to get a copy of that first release.



