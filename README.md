# Generic Estimation Learning Control Simulator

Simulator for testing state estimation (Kalman Filter, Extended Kalman Filter, Unscented Kalman Filter, etc), Machine Learning (classical, deep learning, etc), and Control (classical, optimal, robust, adaptive)  algorithms on general models.


	<li>
<ol>
 	<li>CS Tools: C++, Python, Modern OpenGL</li>
 	<li>Mathematical Tools: Fluid Mechanics, Linear Algebra, Control Theory, Differential Equations, Machine Learning
<ol>
 	<li>General Framework and API (in process)</li>
 	<li>Atmospheric Landing Module Control and Estimation (to be implemented with students in MATH 4900, Spring 2017)</li>
 	<li>Aircraft Simulation Module - Not Implemented</li>
 	<li></li>
	
# TODO

 - [X] Basic Qt GUI setup
 - [X] Basic modular OOP framework setup with OpenGL wrappers for 3D graphics
 - [X] Two body problem simulation using Runge-Kutta integrator 
 - [X] 3DoF Car Module with PID control algorithm and adaptive cruise control
 - [] Testing, bug fixes, optimize code design for modularity and OOP
 - [] Atmospheric Landing Module Control and Estimation
 - [] Statistical Orbit Determination Module
 - [] Optimize code design for modularity and OOP
 - [] Add Generic Estimation and Learning Simulation
 - [] Optimize code design for modularity and OOP
 - [] Full 6DoF modular and OO simulator

[//]: # (Image References)

 [screenshot]: ./SimulatorScreenShot.png "Screenshot"

![Screenshot][screenshot]

# License

GNU LGPL license.

# References

I used several very helpful online tutorials in the initial version of the simulator.

I learned how to do OpenGL in Qt with the following tutorial (Input and Camera classes were also adapted from here)
http://www.trentreed.net/blog/qt5-opengl-part-1-basic-rendering/

Terrain class is based on the following tutorial which I adapted to Qt framework for basic terrain loading:
https://www.3dgep.com/multi-textured-terrain-in-opengl/

I learned about the OBJ files for 3D models and a basic loader from the Modern OpenGL tutorial at:
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

Initial testing car meshes were loaded based on car obj file in:
http://people.sc.fsu.edu/~jburkardt/data/obj/obj.html

Advanced PID controller is designed by students in my MATH 4900 class.

# Notes to self

Adding python interfaces

add in the pro file (add through right-click on the project -> Add Library)


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Applications/anaconda/lib/release/ -lpython3.5m
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Applications/anaconda/lib/debug/ -lpython3.5m
else:unix: LIBS += -L$$PWD/../../../../Applications/anaconda/lib/ -lpython3.5m

INCLUDEPATH += $$PWD/../../../../Applications/anaconda/include/python3.5m
DEPENDPATH += $$PWD/../../../../Applications/anaconda/include/python3.5m
CONFIG += no_keywords

- had to rename libJPEG.dylib; libTIFF.dylib; libPng.dylib; libsqlite3.0.dylib to avoid linker confusion
