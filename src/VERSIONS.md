# CV-Workbench Version History

Descriptions of each branch, commit, and version of CV-Workbench.
- directory  
`$WIN_HOME/DropBox/software/projects/cv/cv-workbench`

#### v0.1.3
```
commit e690983afb190d2d6d7ce2c1c418eb917214defa 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Thu Jun 23 21:24:45 2022 -0600
```
- operator filter-edge-sobel, operator transform-intensity-map, Kernel working

#### v0.1.2
```
commit b9b4a7a783dcc8c504dac0fc659c3680511900dd 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Wed Jun 22 13:09:39 2022 -0600
```
- operator transform-intensity-map works

#### v0.1.1
```
commit 47af0ad1c504a950498559ca4119488218c86d26 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Sun Jun 19 12:19:38 2022 -0600
```
- image-test works
- image-dump has char mode

#### v0.1.0
```
  commit ffae304a1fdafae2e1b94a614230e2e153632257  
  (HEAD -> master, origin/master, origin/HEAD)
  Author: Todd Kushner <kushnertodd@gmail.com>  
  Date:   Fri Jun 17 20:11:03 2022 -0600
```
- `src/parse_experiment_json.cpp` takes `320x240gray.jpg` and produces `320x240gray_sobel.bin`   
  `./parse_experiment_json  ../config/experiment1-definition.json`
- `src/image-test.cpp` produces `image-test-8U.bin` (2x2 image = 'test'; 
segvs at end)
- `examples/c/image-dump.cpp` dumps above binary file  
```
./image-dump image-test.bin
  rows 2 cols 2 components 1 depth CV_8U npixels 4
  0x74 0x65 0x73 0x74
```


