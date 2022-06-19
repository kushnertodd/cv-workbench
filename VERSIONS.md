# CV-Workbench Version History

Descriptions of each branch, commit, and version of CV-Workbench.
- directory  
`$WIN_HOME/DropBox/software/projects/cv/cv-workbench`
#### V 0.1.0
  commit ffae304a1fdafae2e1b94a614230e2e153632257  
  (HEAD -> master, origin/master, origin/HEAD)  
  Author: Todd Kushner <kushnertodd@gmail.com>  
  Date:   Fri Jun 17 20:11:03 2022 -0600
- `src/parse_experiment_json.cpp` takes `320x240gray.jpg` and produces `sobel.jpg`
  (should be `320x240gray_sobel.jpg`)   
  `./parse_experiment_json  ../config/experiment1-definition.json`
- `src/image-test.cpp` produces `image-test-8U.bin` (2x2 image = 'test'; 
segvs at end)
- `examples/c/image-dump.cpp` dumps above binary file  
```
./image-dump image-test.bin
  rows 2 cols 2 components 1 depth CV_8U npixels 4
  0x74 0x65 0x73 0x74
```

