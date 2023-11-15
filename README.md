# Jon Macey Point Visualiser 

## Overview

Point data visualization. 

What is the data format? CSV using different delimiters.

```' ' '\t' ',' ';'```

Where is this data coming from? Writing my own data using a simple C++ or python program. 

Simples format is just a single frame of points.

```
1.0 0.2 0.2
1.0 0.2 0.3
1.0 0.2 0.4
1.0 0.2 0.5
1.0 0.2 0.5
1.0 0.2 0.6
1.0 0.2 0.7
```

Basically need to generate and load this data, then test for it. 

Per frame data, so we need to indicate a frame and perhaps a frame time / number

```
Frame 0 # could be int or float or double so test?
0.2 0.0 0.0
Frame 1
0.2 0.1 0.0
Frane n

```

Final part of the data.

```
Frame 0 

Frame 1
0.1 0.2 0.3

Frame 2
0.0 0.0 .0
0.1 0.2 0.4
```

GPU's in OpenGL have inputs. 

Vec4 -> 0..15 4*16 = 64 floats

