# Computer Graphics Programming Assignment 1

## Ques 1. (3 marks)

_This question is implemented by Itisha Patidar (B17CS026)._

The midpoint line drawing algorithm is implemented in C++. The program randomly generates x and y-coordinates for 2 points with in the range 10-400 for both x and y coordinates. It then draws the line from point-1 to point-2.

_The code can be found in file named [Line_Drawing.cpp](Line_Drawing.cpp)_

#### Output:

![Line_Drawing_Output](https://raw.githubusercontent.com/Itisha2987/CG-Programming_assignment1/main/Line_Drawing_Output.png)

## Ques 2. (5 marks)

_This question is implemented by Geetesh Gupta (B17CS024)._

### Part A

The triangle rasterization using Boundary Box Algorithm with barycentric coordinates is implemented in C++.

The program generates a triangle with coordinates within the range 10-400 for both x and y coordinates.

_The code can be found in file named [Triangle_BoundaryBox.cpp](Triangle_BoundaryBox.cpp)_

### Part B

The triangle rasterization using extended Midpoint Line Algorithm is implemented in C++.

The program generates a triangle with coordinates within the range 10-400 for both x and y coordinates.

The Midpoint Line algorithm first generates the boundaries using the coordinates and then, row-by-row scan to fill the pixels lying between the boundaries generated.

_The code can be found in file named [Triangle_ExtendedLine.cpp](Triangle_ExtendedLine.cpp)_

### Part C

The triangle rasterization using Boundary Box Algorithm and applying SuperSampling at 4x resolution is implemented in C++.

The program generates a traingle with coordinates within the range 10-400 for both x and y coordinates by first generating a buffer matrix with 4x size and coordinates, applying the Part A algorithm and then averaging back in terms of 4x4 matrix and displaying the result.

_The code can be found in file named [Triangle_Supersampling.cpp](Triangle_Supersampling.cpp)_

#### Output:

![Triangle_Output](https://raw.githubusercontent.com/Itisha2987/CG-Programming_assignment1/main/Triangle_Output.jpeg)

## Ques 3. (2 marks)

_This question is implemented by Itisha Patidar (B17CS026)._

The midpoint Circle drawing algorithm is implemented in C++. The program generates a circular arc from 135-215 degree.

_The code can be found in file named [Circle_Drawing.cpp](Circle_Drawing.cpp)_

#### Output:

![Circle_Drawing_Output](https://raw.githubusercontent.com/Itisha2987/CG-Programming_assignment1/main/Circle_Drawing_Output.png)

## Steps to run the code

Standard OpenGL for CPP procedures are to followed to run the files.

### Steps to run in Windows:

### Steps to run in Linux:
