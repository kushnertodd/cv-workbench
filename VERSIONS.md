# CV-Workbench Version History

Descriptions of each branch, commit, and version of CV-Workbench.
- directory  
`$WIN_HOME/DropBox/software/projects/cv/cv-workbench`

#### v0.1.12
```
commit 0db78d78546fb008f1104983819fac36549b8d15 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Wed Jul 13 15:31:32 2022 -0600
```
- modified config/experiment-square45-90-sobel-hough_lines.json to run two hough lines (0,3) and (0,-162)

#### v0.1.11
```
commit 1a50f25020d7b38456dbdd7718eed61a2e54d70f 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Wed Jul 13 15:21:11 2022 -0600
```
- operator hough-draw-line working with config/experiment-square45-90-sobel-hough_lines.json

#### v0.1.10
```
commit c966b587ffd6bf1329d31cfea308f8cf8195905f 
(HEAD -> master, origin/master, origin/HEAD)
  Author: Todd Kushner <kushnertodd@gmail.com>
  Date:   Wed Jul 13 14:34:29 2022 -0600
```
- added generating jpeg hough image with lines to Operator_hough_accumulator_create

#### v0.1.9
```
commit 07070b8607b9eb7f7775773025ee282ae59dfc80 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Wed Jul 13 14:15:34 2022 -0600
```
- Operator_hough_accumulator_create runs with script experiment-square45-90-sobel-hough.sh and script config/experiment-square45-90-sobel-hough

#### v0.1.8
```
commit cb8e00884627c43d6d95d1717d534dfc8ba75b8c 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Mon Jul 11 16:12:14 2022 -0600
```
- operator-transform-intensity-map works


#### v0.1.7
```
commit 29d835c3c8dffcb84858ed81681599c9b0ad30da 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Mon Jul 11 10:26:57 2022 -0600
```
- image-polar.cpp works, image-polar.sh runs, image-polar-run has images

#### v0.1.7
```
commit bd74de7fdf47dd9eb7761ea1b049eb24c006baf6 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Fri Jul 8 20:12:54 2022 -0600
```
- hough working with correct window clipping

#### v0.1.6
```
commit 3f77c8ec6225b5f806826c44c656f8d2fdf53279 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Fri Jul 1 18:55:40 2022 -0600
```
- image-hough with drawing hough line works, found most significant 7 hough lines

#### v0.1.5
```
commit 1037a5a4dc647a60e26328cb3cb5a5c5d66e36c6
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Wed Jun 29 20:02:48 2022 -0600
```
- image-hough, Hough/Hough_accum class work
- 
#### v0.1.5
```
commit 8e6745fe7dfcf17625fba599203181dc5796c61a 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Sun Jun 26 20:14:29 2022 -0600
```
- image-hough works
- run with:  
  `./image-hough image-32S.bin`
- hough accumulator in *image-32S.bin*`.hough.txt`

#### v0.1.4
```
commit bd928d0da6ea1daa5b1a65ac5b649e96c578d385 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Fri Jun 24 13:34:36 2022 -0600
```
- added filter-edge-kirsch, filter-edge-prewitt, and filter-edge-roberts operators
- update variance_stats.cpp, image-stats.cpp, and image-info.cpp

#### v0.1.3
```
ccommit 45c09b4f49c2bd44d5497e62de3c53c4a3c0fb4a 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Thu Jun 23 21:33:14 2022 -0600
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
  rows 2 cols 2 components 1 depth cv_enums::CV_8U npixels 4
  0x74 0x65 0x73 0x74
```

