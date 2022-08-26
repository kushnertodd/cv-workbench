PRAGMA foreign_keys = OFF;
BEGIN
  TRANSACTION;
  CREATE TABLE IF NOT EXISTS "operator_class"
    (
      "name"       TEXT (0) NOT NULL
    ,"description" TEXT (0) NOT NULL
    ,"id"          INTEGER NOT NULL
    ,"domain_id"   INTEGER NOT NULL
    , CONSTRAINT "PK_" PRIMARY KEY ("id")
    , CONSTRAINT "to_domain" FOREIGN KEY ("domain_id") REFERENCES "operator_domain" ("id")
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'edge detectors'
    ,'detects significant local changes in intensity'
    , 1
    , 1
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'convolutions'
    ,'multiply a window around a pixel by a like-sized kernel matrix, substituting the pixel with the sum'
    , 2
    , 1
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'thresholding'
    ,'segment pixel values based on a threshold value'
    , 3
    , 1
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'intensity mapping'
    ,'changing pixel values using a function or looking it up in a table'
    , 4
    , 1
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'smoothing'
    ,'averaging pixel values with neighborhood'
    , 5
    , 1
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'pattern matching'
    ,'finding where a partial image is most likely found in an image'
    , 6
    , 2
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'feature matching'
    ,'finding where shapes are most like to be in an image'
    , 7
    , 2
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'region growing'
    ,'finding contiguous sets of pixel values'
    , 8
    , 3
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'region classification'
    ,'characterizing parameters of regions and identifying patterns'
    , 9
    , 3
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'hough transforms'
    ,'detect lines or shapes using segmented points'
    , 10
    , 3
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'morphological operations'
    ,'changing boundary shapes in binary images'
    , 11
    , 4
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'histogramming pixels'
    ,'creating pixel value frequency distributions'
    , 12
    , 5
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'feature histogramming'
    ,'creating frequency distributions of feature measures'
    , 13
    , 5
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'histogram equilization'
    ,'creating more even pixel value distribution'
    , 14
    , 5
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'threshold selection'
    ,'partition pixel values for optimal segmentation'
    , 15
    , 5
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'image transforms'
    ,'changing image based on functions of all pixel values'
    , 16
    , 6
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'image coding'
    ,'encoding pixel values'
    , 17
    , 6
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'image compression'
    ,'creating reduced size images'
    , 18
    , 6
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'resampling'
    ,'resizing, translating, or rotating image'
    , 19
    , 7
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'warping'
    ,'changing image projection'
    , 20
    , 7
    )
  ;
  
  INSERT INTO operator_class VALUES
    ( 'pyramids'
    ,'representing images at multiple resolution levels'
    , 21
    , 7
    )
  ;
  
  CREATE TABLE IF NOT EXISTS "operator_domain"
    (
      "id"         INTEGER NOT NULL
    ,"name"        TEXT (0) NOT NULL
    ,"description" TEXT (0) NOT NULL
    , CONSTRAINT "PK_" PRIMARY KEY ("id")
    )
  ;
  
  INSERT INTO operator_domain VALUES
    ( 1
    ,'filters'
    , replace('pixel-level operators that transform pixels or \nmake computations on pixel neighborhoods that are stored in pixels.', '\n', CHAR(10))
    )
  ;
  
  INSERT INTO operator_domain VALUES
    ( 2
    ,'correlation'
    ,'matching features or patterns of image values to image.'
    )
  ;
  
  INSERT INTO operator_domain VALUES
    ( 3
    ,'feature detection'
    , replace(replace('region-level operators to detect and characterize.\r\narbitrary shaped areas in images.', '\r', CHAR(13)), '\n', CHAR(10))
    )
  ;
  
  INSERT INTO operator_domain VALUES
    ( 4
    ,'binary operators'
    ,'transformations of binary images.'
    )
  ;
  
  INSERT INTO operator_domain VALUES
    ( 5
    ,'histogram operators'
    , replace(replace('creating, transforming, or extracting.\r\nparameters of histograms', '\r', CHAR(13)), '\n', CHAR(10))
    )
  ;
  
  INSERT INTO operator_domain VALUES
    ( 6
    ,'image operators'
    ,'various image-wide transforms.'
    )
  ;
  
  INSERT INTO operator_domain VALUES
    ( 7
    ,'geometric operations'
    ,'projecting images based on different viewing geometries.'
    )
  ;
  
  CREATE TABLE IF NOT EXISTS "operator_instance"
    (
      "name"       TEXT (0) NOT NULL
    ,"description" TEXT (0) NOT NULL
    ,"id"          INTEGER NOT NULL
    ,"class_id"    INTEGER NOT NULL
    , CONSTRAINT "PK_" PRIMARY KEY ("id")
    , CONSTRAINT "to_class" FOREIGN KEY ("class_id") REFERENCES "operator_class" ("id")
    )
  ;
  
  CREATE TABLE IF NOT EXISTS "operator_definition"
    (
      "id"           INTEGER NOT NULL
    ,"name"          TEXT (0) NOT NULL
    ,"description"   TEXT (0) NOT NULL
    ,"instance_id"   INTEGER NOT NULL
    ,"version"       INTEGER NOT NULL
    ,"parameters_id" INTEGER NOT NULL
    , CONSTRAINT "PK_" PRIMARY KEY ("id")
    , CONSTRAINT "to_instance" FOREIGN KEY ("instance_id") REFERENCES "operator_instance" ("id")
    )
  ;
  
  CREATE TABLE IF NOT EXISTS "experiment_steps"
    (
      "id"           INTEGER NOT NULL
    ,"name"          TEXT (0) NOT NULL
    ,"description"   TEXT (0) NOT NULL
    ,"experiment_id" INTEGER NOT NULL
    ,"definition_id" INTEGER NOT NULL
    , CONSTRAINT "PK_" PRIMARY KEY ("id")
    , CONSTRAINT "to_definition" FOREIGN KEY ("definition_id") REFERENCES "operator_definition" ("id")
    , CONSTRAINT "to_experiment" FOREIGN KEY ("experiment_id") REFERENCES "experiment" ("id")
    )
  ;
  
  CREATE TABLE IF NOT EXISTS "experiment_implementers"
    (
      "id"           INTEGER NOT NULL
    ,"experiment_id" INTEGER NOT NULL
    ,"agent_id"      INTEGER NOT NULL
    , CONSTRAINT "PK_" PRIMARY KEY ("id")
    , CONSTRAINT "agent_experiment" FOREIGN KEY ("experiment_id") REFERENCES "experiment" ("id")
    , CONSTRAINT "experiment_agent" FOREIGN KEY ("agent_id") REFERENCES "agent" ("id")
    )
  ;
  
  CREATE TABLE IF NOT EXISTS "experiment_designers"
    (
      "id"           INTEGER NOT NULL
    ,"experiment_id" INTEGER NOT NULL
    ,"agent_id"      INTEGER NOT NULL
    , CONSTRAINT "PK_" PRIMARY KEY ("id")
    , CONSTRAINT "agent_experiment" FOREIGN KEY ("experiment_id") REFERENCES "experiment" ("id")
    , CONSTRAINT "experiment_agent" FOREIGN KEY ("agent_id") REFERENCES "agent" ("id")
    )
  ;
  
  CREATE TABLE IF NOT EXISTS "experiment"
    (
      "id"         INTEGER NOT NULL
    ,"name"        TEXT (0) NOT NULL
    ,"description" TEXT (0) NOT NULL
    , CONSTRAINT "PK_" PRIMARY KEY ("id")
    )
  ;
  
  CREATE TABLE IF NOT EXISTS "agent"
    (
      "id"         INTEGER NOT NULL
    ,"name"        TEXT (0) NOT NULL
    ,"description" TEXT (0) NOT NULL
    , CONSTRAINT "PK_" PRIMARY KEY ("id")
    )
  ;
  
  DELETE
  FROM
    sqlite_sequence
  ;
  
  COMMIT;
