# AutoCuber
A fully automated Rubik's cube solving machine

### Video demonstration
Stage 1: Scan all 6 faces of the cube to retrieve cube state

Stage 2: Calculate solution and solve

https://www.youtube.com/watch?v=FX_zLw3P7Gw


### Organisation
- `Designs` contains 3D models created for this project (as well as the custom PCB design)
- `RPI` contains the python programs written to scan in a cube's state and calculate a solution (used on RPI3B w/ Cam)
- The root directory contains the C++ program to control the stepper motors and interpret serial communication (Arduino Mega)

### How does it work?
#### Cube interaction
The machine is similar to others you may have seen before. 4 stepper motors on linear rails are able to turn faces of the cube
in the horizontal plane. 4 more stepper motors attached using a rod can pull and push the other stepper motors along their rails.
Through this system, it is possible to turn any face of the cube, either directly or after rotating the cube. All the motors are 
controlled by DRV8825 stepper motor drivers, connected to an Arduino Mega. The stepper motor drivers are soldered to two identical custom PCBs.
#### Finding the cube's state
A Raspberry Pi 3B is used with a camera to take an image of each face of the cube (Commands are sent to the Arduino Mega to rotate
the cube such that the face needed is facing the camera). The picture is cropped and rotated by a fixed constant amount to contain
only the face of the cube. It is then split into 9 equal segments to isolate individual tiles. k-means clustering is used to find
the dominant colour in each tile. This RGB value is converted to HSL such that linear comparisons can be made between colours. The 
shortest euclidian distance is used to determine which class the colour belongs to. The entire cube is then mapped using this technique.
#### Solving the cube
The `ckociemba` library is used to find a solution using Kociemba's method. The set of instructions to solve the cube are sent 
one by one to the Arduino Mega which uses the motors to complete each move on the cube. **TODO: A custom implementation of 
Kociemba's algorithm.**
