![Logo](Docs/g10154.png)
# team11_RTEP5: Mechanised User vs. Computer Chess Board
Computer chess engines have become very advanced and are great for learning how to play or for improving your skills. However, playing on a computer is just not the same as seeing the physical pieces move across the board!

This project aims to design and build a mechanised chess device, allowing users to play against the StockFish chess engine on a physical board. An X-Y positioning table will use an electromagnet to execute the computer-generated moves, moving the physical pieces across the board, mimicking a real chess expert.

![Layers of the system](Docs/path7416.png)

# why?
Playing games on a computer screen can be great - but it takes away from the game. Ghost Chess allows users to detach from their everyday computer use to really invest in the game itself, providing a more engaging gaming experience. Variable difficulty levels allow users to improve their chess skills. Not to mention that it is really cool!

## Table of Contents
[Getting Started](#getting_started)
  * [Required Hardware](#required_hardware)
  * [Building Software](#building_software)
  * [System Specification](#system_specification)

# Getting Started <a name="getting_started"></a>
All project-related software can be found in folder "src", and all required schematics/CAD files/PCB designs/footprints are located in folder "Docs".
## Required Hardware and Parts <a name="required_hardware"></a>
* The full Bill of Materials can be found on this link (still being updated): goo.gl/mntyCQ
X-Y positioning:
* 3x Stepper Motors (Nema 17)
* 3x Stepper motor drivers (Pololu A4988)
* 1x Electromagnet (3/4' Diameter, 4.5kg pull force) and 40x Button Magnets (3mm diameter, 2mm height)
* transistor
* 2x 700/900 mm plywood sheets
* 2x 700mm and 1x 500mm T-slot bar
* 3x 125mm oak shuttles
* 6x T-bolts
* 1x 500mm oak bar
* 6x 40T GT2 6mm Timing Pulley
* 5M 6mm GT2 fiber-glass re-enforced rubber timing belt
* 1x 500mm metal shaft and 1x 30mm metal shaft
* 6x Flanged Corner Bracket BZP

Sensor Matrix:
* 72x Latching Hall-effect Sensors (SS361RT) and 72 10kohm resistors
* 2x 8-1 FET Mux/Demux (SN74CBT3251)

Other:
* Laser-cut Acrylic chess board and 3D printed pieces
* Raspberry Pi 3 Model B

# Assembling the mechanical arm:
![Logo](Docs/XYplaneDiag.png)

All measurements in mm.

A Plywood base is used to ensure that there is no unwanted lateral motion under tension. T-slot bars act as runners for oak shuttles, held in place by T-bolts. The Y plane movement is supported by two T-slot bars, each 700mm in length. Mounted to both the Oak shuttles on the Y plane is an oak bar which holds the 3rd, X plane, T-slot bar in place (500mm in length). Each shuttle is moved using a timing belt which is mounted through 2 pulleys to a stepper motor.

![Logo](Docs/20180326_152725.jpg | width=50)

1. Cut and bevel the two 915mm/70mm Plywood sheets which form the base and top plate of the design
![Logo](Docs/img/20180326_102938.jpg | width=50)

2. Bolt down the 2 700mm length T-slot bars through the base plywood sheet (4 bolts spaced evenly)
![Logo](Docs/20180326_133212.jpg =250x250)

3. Cut the 3 125mm/35mm oak shuttles and the 500mm/35mm oak cross bar
4. Mount the oak cross bar to two of the oak shuttles using miter-fast bond and screws
![](Docs/20180326_135516.jpg =250x250)

5. Bolt the 500mm T-slot bar to the oak cross bar (4 bolts spaced evenly)
1[](Docs/20180326_152722.jpg =250x250)

6. Cut oak blocks to stand the pulleys and motors (x6, 3 for motors and 3 for pulleys), plane to match heights (the bottom of the pulleys should be at the same height as the top of the oak shuttles to ensure that the timing belt can be fixed securely)
7. Fix the oak blocks to the plywood base using miter fast bond and screws
![](Docs/20180327_145121.jpg =250x250)

8. fix the flaged corner brackets to the oak blocks, ensuring they are parallel to the T-slot bar and in line
9. attach the motors to the flanged corner brackets by drilling holes in the corner bracket and bolting the motors through them
10. attach pulleys to motor shafts, 500mm metal shaft, and 30mm metal shaft
![](Docs/20180327_125229.jpg =250x250)
![](Docs/20180328_183312.jpg =250x250)

11. attach timing belt to oak shuttles through pulleys with tension using miter fast bond

# Electromagnet

The electromagnet is controlled using a GPIO enable, connected to the gate of a transistor with 12V DC from the power supply connected to source and the drain connected to ground.

# Sensor matrix: detecting the users move

## Building Software <a name="building_software"></a>
![GUU](Docs/GhostChessGUI.png)
To build this project's software: first clone the repository then run

```
cmake .
make

./main

```

# Software Flow:

The software forms an interface between the user and the StockFish API, updating the API with new moves and reading out the computers moves to pass to the motor control software. A full software flow diagram can be found in Docs/Software_flow_diagram.png

# Motor control:

Motor control is performed using digital GPIO outputs which control the Pololu A4988 stepper motor driver. The stepper motors are rotated in 4 stages which relates to 4 configurations of the H-bridge inductor which is used to turn the motor shaft. A single rotation therefore relates to:

To move pieces accross the board the control software performs the following steps:
1. Move to coordinate y1 x1 (the coordinate of the piece to be moved)
2. Turn on electro magnet
3. Move to edge of square (to ensure that the peice being moved will not collide with any pieces in surrounding squares)
4. Move to coordinate y2 x2 (the space to be moved to)
5. Return piece to the centre of the square
6. Return to origin of the board (located at square A1)

## System Specification <a name="system_specification"></a>

Responsiveness of the system. How long the system will take to move a piece.
Latency permitted for the piece -> dependant on where the piece has to move (
Sampling rate of 2Hz? for board state of 64 elements
Bus Protocol? 
Channels? 1
Kernel or userspace + why
data flow (formats, latencies, processing and conversions)
Buffering and sample size
  -> latency introduced from buffering?
Postprocessing of data and how that introduces latencies / processor load?
  -> Post processing of the data (sample rates sufficiently slow perhaps)
 
Threads/ load distributing ? ensure responsiveness

QT GUI permitted refresh rate and latency introduced (may not be so much of an issue since our sample rates are slow)

Structure software in classes, associated unit tests

### Team Roles
* Alex Angelov - 3D Pieces Modelling, Board Production, Position Sensing and Related Software
* Tim Ness - Design Assembly, Accurate Motor Control and Related Software
* Alex Smith - Chess Engine Integration and QT GUI Interface

# Progress Success Evaluation
Issue tracking and Project Tracking through github's associated tools.

How does the project acheive the goals that are set out above?

## FAQ/Common Issues

