CREATE TABLE sqlite_sequence
  (
    name
  , seq
  )
;

CREATE TABLE IF NOT EXISTS "operator_class"
  (
    "name"        TEXT (0) NOT NULL
  , "description" TEXT (0) NOT NULL
  , "id"          INTEGER NOT NULL
  , "domain_id"   INTEGER NOT NULL
  , CONSTRAINT "PK_" PRIMARY KEY ( "id" )
  , CONSTRAINT "to_domain" FOREIGN KEY ( "domain_id" ) REFERENCES "operator_domain" ( "id" )
  )
;

CREATE TABLE IF NOT EXISTS "operator_domain"
  (
    "id"          INTEGER NOT NULL
  , "name"        TEXT (0) NOT NULL
  , "description" TEXT (0) NOT NULL
  , CONSTRAINT "PK_" PRIMARY KEY ( "id" )
  )
;

CREATE TABLE IF NOT EXISTS "operator_instance"
  (
    "name"        TEXT (0) NOT NULL
  , "description" TEXT (0) NOT NULL
  , "id"          INTEGER NOT NULL
  , "class_id"    INTEGER NOT NULL
  , CONSTRAINT "PK_" PRIMARY KEY ( "id" )
  , CONSTRAINT "to_class" FOREIGN KEY ( "class_id" ) REFERENCES "operator_class" ( "id" )
  )
;

CREATE TABLE IF NOT EXISTS "experiment_run"
  (
    "id"                    INTEGER NOT NULL
  , "timestamp"             INTEGER NOT NULL
  , "definition_id"         INTEGER NOT NULL
  , "implementer_id"        INTEGER NOT NULL
  , "name"                  TEXT (0) NOT NULL
  , "description"           TEXT (0) NOT NULL
  , "notes"                 TEXT NOT NULL
  , "experiment_version_id" INTEGER NOT NULL
  , CONSTRAINT "PK_" PRIMARY KEY ( "id" )
  , CONSTRAINT "run_agent" FOREIGN KEY ( "implementer_id" ) REFERENCES "experiment_implementers" ( "id" )
  , CONSTRAINT "run_definition" FOREIGN KEY ( "definition_id" ) REFERENCES "experiment_definition" ( "id" )
  )
;

CREATE TABLE IF NOT EXISTS "operator_instance_version"
  (
    "id"          INTEGER NOT NULL
  , "name"        TEXT (0) NOT NULL
  , "description" TEXT (0) NOT NULL
  , "instance_id" INTEGER NOT NULL
  , "version"     INTEGER NOT NULL
  , "template_id" INTEGER NOT NULL
  , CONSTRAINT "PK_" PRIMARY KEY ( "id" )
  , CONSTRAINT "to_operator_instance" FOREIGN KEY ( "instance_id" ) REFERENCES "operator_instance" ( "id" )
  )
;

CREATE TABLE IF NOT EXISTS "agents"
  (
    "id"          INTEGER NOT NULL
  , "name"        TEXT (0) NOT NULL
  , "description" TEXT (0) NOT NULL
  , CONSTRAINT "PK_" PRIMARY KEY ( "id" )
  )
;

CREATE TABLE IF NOT EXISTS "output_images"
  (
    "id"                           INTEGER NOT NULL
  , "name"                         TEXT (0) NOT NULL
  , "description"                  TEXT (0) NOT NULL
  , "experiment_step_run_id"       INTEGER NOT NULL
  , "image_id"                     INTEGER NOT NULL
  , "operator_instance_version_id" INTEGER NOT NULL
  , "output_image_type_id"         INTEGER NOT NULL
  , CONSTRAINT "to_experment_step_run" FOREIGN KEY ( "experiment_step_run_id" ) REFERENCES "experiment_step_run" ( "id" )
  , CONSTRAINT "to_output_image_type" FOREIGN KEY ( "output_image_type_id" ) REFERENCES "output_image_type" ( "id" )
  )
;

CREATE TABLE IF NOT EXISTS "output_image_type"
  (
    "id"                           INTEGER NOT NULL
  , "name"                         TEXT (0) NOT NULL
  , "description"                  TEXT (0) NOT NULL
  , "operator_instance_version_id" INTEGER NOT NULL
  , CONSTRAINT "to_operator_instance_version" FOREIGN KEY ( "operator_instance_version_id" ) REFERENCES "operator_instance_version" ( "id" )
  )
;

CREATE TABLE IF NOT EXISTS "input_images"
  (
    "id"                     INTEGER NOT NULL
  , "name"                   TEXT (0) NOT NULL
  , "description"            TEXT (0) NOT NULL
  , "experiment_step_run_id" INTEGER NOT NULL
  , "image_id"               INTEGER NOT NULL
  , "input_image_type_id"    INTEGER NOT NULL
  , CONSTRAINT "to_experment_step_run" FOREIGN KEY ( "experiment_step_run_id" ) REFERENCES "experiment_step_run" ( "id" )
  , CONSTRAINT "to_input_image_type" FOREIGN KEY ( "input_image_type_id" ) REFERENCES "input_image_type" ( "id" )
  )
;

CREATE TABLE IF NOT EXISTS "input_image_type"
  (
    "id"                           INTEGER NOT NULL
  , "name"                         TEXT (0) NOT NULL
  , "description"                  TEXT (0) NOT NULL
  , "operator_instance_version_id" INTEGER NOT NULL
  , CONSTRAINT "to_operator_instance_version" FOREIGN KEY ( "operator_instance_version_id" ) REFERENCES "operator_instance_version" ( "id" )
  )
;

CREATE TABLE IF NOT EXISTS "experiment_version"
  (
    "id"          INTEGER NOT NULL
  , "name"        TEXT (0) NOT NULL
  , "description" TEXT (0) NOT NULL
  , "designer_id" INTEGER NOT NULL
  , "version"     INTEGER NOT NULL
  , CONSTRAINT "PK_" PRIMARY KEY ( "id" )
  , CONSTRAINT "to_designer" FOREIGN KEY ( "designer_id" ) REFERENCES "agents" ( "id" )
  )
;

CREATE TABLE IF NOT EXISTS "experiment_step_version"
  (
    "id"                           INTEGER NOT NULL
  , "name"                         TEXT (0) NOT NULL
  , "description"                  TEXT (0) NOT NULL
  , "experiment_version_id"        INTEGER NOT NULL
  , "designer_id"                  INTEGER NOT NULL
  , "version"                      INTEGER NOT NULL
  , "operator_instance_version_id" INTEGER NOT NULL
  , "template_id"                  INTEGER NOT NULL
  , CONSTRAINT "PK_" PRIMARY KEY ( "id" )
  , CONSTRAINT "to_designer" FOREIGN KEY ( "designer_id" ) REFERENCES "agents" ( "id" )
  , CONSTRAINT "to_experiment_version" FOREIGN KEY ( "experiment_version_id" ) REFERENCES "experiment_version" ( "id" )
  , CONSTRAINT "to_operator_instance_version" FOREIGN KEY ( "operator_instance_version_id" ) REFERENCES "operator_instance_version" ( "id" )
  )
;

CREATE TABLE IF NOT EXISTS "experiment_step_run"
  (
    "id"                           INTEGER NOT NULL
  , "name"                         TEXT (0) NOT NULL
  , "description"                  TEXT (0) NOT NULL
  , "experiment_step_version_id"   INTEGER NOT NULL
  , "implementer_id"               INTEGER NOT NULL
  , "notes"                        TEXT (0) NOT NULL
  , "operator_instance_version_id" INTEGER NOT NULL
  , "parameter_id"                 INTEGER NOT NULL
  , "timestamp"                    INTEGER NOT NULL
  , CONSTRAINT "PK_" PRIMARY KEY ( "id" )
  , CONSTRAINT "to_experiment_run" FOREIGN KEY ( "name" ) REFERENCES "experiment_run" ( "id" )
  , CONSTRAINT "to_experiment_step_version" FOREIGN KEY ( "experiment_step_version_id" ) REFERENCES "experiment_step_run" ( "id" )
  , CONSTRAINT "to_implementer" FOREIGN KEY ( "id" ) REFERENCES "experiment_step_run" ( "id" )
  )
;