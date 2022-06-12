# Testing

## image-test
to test:

- input is color `320x240color.jpg`
- convert to graysacle `320x240gray.jpg`
```
jpegtran -grayscale 320x240color.jpg >320x240gray.jpg
```
- build image_test
```
make image_test
```
- run image_test

produces `320x240gray_out.jpg` which should be visibly identical to
`320x240gray.jpg`, though is not binary identical.
```
$ ./image_test
test_write
0000000    0002    0000    0002    0000    0001    0000    6574    7473
        stx nul nul nul stx nul nul nul soh nul nul nul   t   e   s   t
0000020
test_read
Image 'test-image.bin'
   rows 2
   cols 2
   components 1
   buf
      0: 't'
      1: 'e'
      2: 's'
      3: 't'
Image '320x240gray.jpg'
   rows 240
   cols 320
   components 1
   buf
      0: ']'
      1: ']'
      2: ']'
      3: ']'
      4: ']'
      5: ']'
      6: ']'
      7: ']'
      8: 'a'
      9: 'a'
```
