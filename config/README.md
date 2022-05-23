# CV-Workbench v0.1

The *CV-Workbench* is a framework to perform reproducible
computer vision experiments. 
A record of the input sources,
processing done, 
and output results will be kept such that experiments
can be reproduced. 
Notes can be retained for individual experiment
runs. 
Experiments can be shared between CV-Workbench instances
installed on different machines.

## Experiments
Each experiment consists of:
- zero or more input images or data structures
- processing steps consisting of computer vision *operators*
- zero or more output image or data structures

Processing steps will be individual command lines
that specify the inputs, an operator, and outputs.
Storing steps as command lines permits storing them
in files as scripts, making reproducing the experiment
more reliable. 
All parameters for a processing step will be specified
on the command line.
Command *templates* will control verifying that
the necessary and correct parameters are specified.
The parameters used in an operation, with the inputs
and outputs, will be stored in the experiment record.

## Data Structures
Computer vision operators each act on specific vision data 
structures.
Among these are:
- images (grayscale, binary, and color)
- histograms
- features
- regions

Each of these may have subtypes and various attributes, such as
that images and histograms have a given size,
features may be points from an edge operator or lines from 
a Hough transform, regions may be boundary points or
fixed geometric regions.
Operators will expect input data structures of the 
right subtypes and valid attributes, and
produce data structures with arbitrary definitions.

Each data structure will be stored before input to the
operator and saved on output.
The characteristics will be stored with the data structures.

## Operators
Each operator corresponds to a standard computer vision
operator supported by CV-Workbench.
Not provided are:
- user defined computer vision operators (unless added to the
  CV-Workbench code)
- having logic control performing the operators
- permit running operators multiple times

These may be added in a later version.

CV-Workbench operators are grouped by a hierarchy of types.
- Operator *domains* are the most general grouping, 
including filtering, matching, morphological, or histogramming.
- Operator *classes* are the next level of grouping, 
such as for the filtering domain, 
including edge detectors, convolutions, thresholding,
or intensity mapping.
- Operator *instances* are the next level, such as for
edge detectors, including Sobel, Roberts, Prewitt, 
- or Kirsch operators.

Operators will have parameters that will control
the kinds of required input characteristics,
the details of the operator processing involved,
and the characteristics of the output produced.

# Experiment Commands
Each command will be a line in a text script.
The format of a command will be:

*command* parameter1 parameter2 ...

The parameters for a command will 
be specified in *templates* describing
each parameter.
The template will determine whether a 
parameter is required, 
the type and constraints on a parameter's value,
and whether a default is available for optional
parameters.
Command functions will include:
- Reading, storing, and modifying input and output data structures.
- Performing computer vision operators on data structures and 
recording results.
- Various maintenance functions such as deleting data
structures, 
creating or removing storage locations,
producing reports from experiments.

## Command Templates
Command templates will be provided for each available workbench
command.
Templates will be stored as *JSON*, 
making them convenient to read to form commands
and store.
Knowledge of [JSON](https://www.json.org/json-en.html) 
will be required to read them.

Command formats will change over time.
Each format change will be recorded as
a different version of a template. 
Every version of a template will be stored
so that previous experiment scripts will still run.
Upgrading scripts to latest versions of templates
will be a task for the experimenter.
The changes involved in the new version,
and instructions to change the scripts,
will be provided when a new version is produced.

### Template format
Each operator template will have the same general format.
Templates will specify:
- a unique id for the template, used to retrieve the stored template.
- the domain, class, and instance of the operator involved.
- an optional comment.
- each possible parameters, including:
  - the parameter name specified in the command.
  - an optional comment.
  - whether the parameter is required.
  - the parameter value data type.
  - the permitted range for numeric values.
  - the permitted values for text values.
  - default value for optional parameters.

These will vary for different operators. 
Each command performing an operator must have a valid name.
```
{
  "operator-name-1": {
    "id": 1,
    "domain": "string",
    "class": "string",
    "instance": "string",
    "_comment1": [
      "line1",
      "line2"
    ],
    "parameters": [
      {
        "_comment1": [
          "line1",
          "line2"
        ],
        "name": "parameter-1",
        "required": "true|false",
        "data-type": "int|real|string|boolean",
        "range": {
          "min-value": "value",
          "max-value": "value"
        },
        "valid-values": [
          "value-1",
          "value-2"
        ]
        "default": "value",
      },
      {
        "name": "parameter-2, etc."
      }
    ]
  }
}
```
An example for a Sobel edge operator is this.
The meaning of the parameters requires 
understanding the Sobel operators.
```
{
  "Sobel": {
    "id": 4,
    "domain": "filters",
    "class": "edge detection",
    "parameters": [
      {
        "__comment1": [
          " 0 = [-1, 0, 1], [-2, 0, 2], [-1, 0, 1]",
          "90 = [1, 2, 1],  [0, 0, 0],  [-1, -2, -1]"
        ],
        "name": "orientation",
        "data-type": "int",
        "default": 0,
        "valid-values": [
          0,
          90
        ]
      }
    ]
  }
}

```

## Command Parameters
In the record of an experiment,
the commands performed and the actual parameters used
in the commands will be stored. 
They will be recorded as JSON text
with parameters matching the template format for them.

## Operator Parameters JSON

These will vary for different operators.
Each command performing an operator must have a valid name.
The parameters JSON will match the template format like this;
```
{
  "operator-name-1": {
    "id": 1,
    "domain": "string",
    "class": "string",
    "instance": "string",
    "parameters": [
      {
        "name": "parameter-1",
        "value": "value",
      },
      {
        "name": "parameter-2, etc."
      }
    ]
  }
}
```
Example parameters for a Sobel edge operator is this.
```
{
  "Sobel": {
    "id": 4,
    "domain": "filters",
    "class": "edge detection",
    "parameters": [
      {
        "name": "orientation",
        "value": 0
      }
    ]
  }
}

```
