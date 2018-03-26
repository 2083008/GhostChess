![Logo](Docs/g10154.png)
# team11_RTEP5: Mechanised User vs. Computer Chess Board
Computer chess engines have become very advanced and are great for learning how to play or improving your skills. However, playing on a computer is just not the same as seeing the physical pieces move across the board!

This project aims to design and build a mechanised chess device, allowing users to play against the StockFish chess engine on a physical board. An X-Y positioning table (stage) will use an electromagnet to execute the computer-generated best moves and move the physical pieces across the board, mimicking a real chess expert.

![Layers of the system](Docs/path7416.png)

# Reasons why?
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
* 3x Stepper Motors (Nema 17)
* 3x Stepper motor drivers (Pololu A4988)
* 1x Electromagnet (3/4' Diameter, 4.5kg pull force) and 40x Button Magnets (3mm diameter, 2mm height)
* 72x Latching Hall-effect Sensors (SS361RT) and 72 10kohm resistors
* 2x 8-1 FET Mux/Demux (SN74CBT3251)
* Laser-cut Acrylic chess board and 3D printed pieces

# Assembling the mechanical arm:
![Logo](Docs/XYplaneDiag.png)
All measurements in mm.

A Plywood base is used to ensure that there is no unwanted lateral motion under tension. T-slot bars act as runners for oak shuttles, held in place by T-bolts. The Y plane movement is supported by two T-slot bars, each 700mm in length. Mounted to both the Oak shuttles on the Y plane is an oak bar which holds the 3rd, X plane, T-slot bar in place. Each shuttle is moved using a timing belt which is mounted through 2 pulleys to a stepper motor.

## Building Software <a name="building_software"></a>
To build this project's software: first clone the repository then run

```
cmake .
make

./main

```

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

