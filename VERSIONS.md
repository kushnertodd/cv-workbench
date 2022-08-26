# CV-Workbench Version History

Descriptions of each branch, commit, and version of CV-Workbench.
- directory  

`$WIN_HOME/DropBox/software/projects/cv/cv-workbench`

#### v0.1.29 dev
```
commit 20b9273669d0fd7ce16cb29909370913541196a7 
(HEAD -> dev, origin/dev)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Thu Aug 25 17:44:37 2022 -0600
```
- version copied to master on 2022-08-25

#### v0.1.28 dev
```
commit 157a0c4b92cf69d92b06ea5b76a635c8c304879a 
(HEAD -> dev, origin/dev)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Tue Aug 16 16:42:23 2022 -0600
```
- filter-smooth-average works

#### v0.1.27 dev
```
commit 5676189757e387f672960b946954de4757566cfc 
(HEAD -> dev, origin/dev)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Sun Aug 14 20:34:26 2022 -0600
```
- filter-image-morphology works

#### v0.1.26 dev
```
commit 1b127a9388b00c2eafe4c4a717e38a0061125dac 
(HEAD -> dev, origin/dev)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Sun Aug 14 18:52:30 2022 -0600
```
- transform-image-create works for point, line, and rectangle

#### v0.1.25 dev
```
commit 0270ac7f697fd1b065ca58e716f56dc9bba561fe
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Fri Aug 12 17:19:09 2022 -0600
```
- hough-image-create verified as correct

#### v0.1.24 dev
```
commit 73af8069ab918fb4d0ffe95d70057d1e24a4eb13 
(HEAD -> dev, origin/dev)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Fri Aug 5 16:36:14 2022 -0600
```
- operator hough-peak-detect works

#### v0.1.23 dev
```
commit a77745fdf88b3cf9a3c5344cb2b2e26a3b39ae3c 
(HEAD -> dev, origin/dev)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Thu Aug 4 16:07:51 2022 -0600
```
- interim checking refactoring filename opening

#### v0.1.22 dev
```
commit c1814b63eb5ea2182d0219262ab4814232b0ce69 
(HEAD -> dev, origin/dev)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Wed Aug 3 09:07:17 2022 -0600
```
- operator-filter-image-morphology works

#### v0.1.21 dev
```
commit 32e123f0ef90028fb935b4e6f7cc1f5767eaba8c 
(HEAD -> dev, origin/dev)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Mon Aug 1 20:02:10 2022 -0600
```
- added transform-image-morphology operator

#### v0.1.20
```
commit f7a881cd2a1590f838f31035797573991e0d481c 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Sun Jul 31 17:38:51 2022 -0600
```
- first alpha release 0.1.20
- sent to CU, U. of Utah, EZ3D
- created dev branch

#### v0.1.19
```
commit 0d19aa7a3cb56a783c12b2a1ceb53fb5179eb902 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Sun Jul 31 16:46:32 2022 -0600
```
- logging added tests working removed warnings

#### v0.1.18
```
commit 65e9460b568854578dbc0d99a1f62f76f63ef3d8 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Sat Jul 30 18:53:47 2022 -0600
```
- logging works

#### v0.1.17
```
commit 983df2a9146fa2c23409cf709485af76a7be87d6 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Fri Jul 29 17:08:40 2022 -0600
```
-  implemented histogram-image and histogram-hough

#### v0.1.16
```
commit aa4268a80f401621b37e3177ff7e8b48fcb5636b 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Thu Jul 21 13:46:29 2022 -0600
```
- added hough accumulator create  test

#### v0.1.15
```
commit 49b0fc7d2667eeddd8725e9c3de8a755aecc33e8 (HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Thu Jul 21 12:21:49 2022 -0600
```
- added prewitt roberts kirsch test

#### v0.1.14
```
commit 4ffec9115af856e1ef8483061e1e3ef2a61b5fda (HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Wed Jul 20 20:21:18 2022 -0600
```
- test both sobel 0/90 deg and hough draw lines sobel 0/90 deg working

#### v0.1.13
```
commit df263dd308ee5be5b2e36389d2e92e29133cc95a 
(HEAD -> master, origin/master, origin/HEAD)
Author: Todd Kushner <kushnertodd@gmail.com>
Date:   Tue Jul 19 20:58:04 2022 -0600
```
- operation hough draw line works (how did Line_segment::add() switch x and y

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
- update_input_value variance_stats.cpp, image-accumulator_stats.cpp, and image-info.cpp

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


