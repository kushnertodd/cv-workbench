/*
PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "operator_class" ( "name" TEXT (0)  NOT NULL , "description" TEXT (0)  NOT NULL , "id" INTEGER  NOT NULL , "domain_id" INTEGER  NOT NULL , CONSTRAINT "PK_" PRIMARY KEY ( "id" ) , CONSTRAINT "to_domain" FOREIGN KEY ( "domain_id" ) REFERENCES "domain" ( "id" ) );
INSERT INTO operator_class VALUES('edge detectors','detects significant local changes in intensity',1,1);
CREATE TABLE IF NOT EXISTS "domain" ( "id" INTEGER  NOT NULL , "name" TEXT (0)  NOT NULL , "description" TEXT (0)  NOT NULL , CONSTRAINT "PK_" PRIMARY KEY ( "id" ) );
*/
INSERT INTO operator_domain VALUES(1,'filters',replace('pixel-level operators that transform pixels or \nmake computations on pixel neighborhoods that are stored in pixels.','\n',char(10)));
INSERT INTO operator_domain VALUES(2,'correlation','matching features or patterns of image values to image.');
INSERT INTO operator_domain VALUES(3,'feature detection',replace(replace('region-level operators to detect and characterize.\r\narbitrary shaped areas in images.','\r',char(13)),'\n',char(10)));
INSERT INTO operator_domain VALUES(4,'binary operators','transformations of binary images.');
INSERT INTO operator_domain VALUES(5,'histogram operators',replace(replace('creating, transforming, or extracting.\r\nparameters of histograms','\r',char(13)),'\n',char(10)));
INSERT INTO operator_domain VALUES(6,'image operators','various image-wide transforms.');
INSERT INTO operator_domain VALUES(7,'geometric operations','projecting images based on different viewing geometries.');
COMMIT;
