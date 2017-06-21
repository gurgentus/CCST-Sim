# Generic Estimation Learning Control Simulator

Simulator for testing state estimation (Kalman Filter, Extended Kalman Filter, Unscented Kalman Filter, etc), Machine Learning (classical, deep learning, etc), and Control (classical, optimal, robust, adaptive)  algorithms on general models.  For speed and flexibility rather than using a game engine like Unity or Unreal, I decided to directly use modern OpenGL with OpenGL Shading Language with a light Qt wrapper.  The GUI is also done in Qt for platform independence.


# TODO

 - [X] Basic Qt GUI setup
 - [X] Basic modular OOP framework setup with OpenGL wrappers for 3D graphics
 - [X] Basic car module with PID control algorithm and adaptive cruise control
 - [X] More realistic car model with steering
 - [X] Satellite orbit determination and restricted three body (Moon mission) orbital mechanics simulations
 - [X] Probabilistic filter module (Kalman, Extended Kalman, Unscented Kalman)
 - [X] Connect probabilistic filter module to orbit determination module (with the state consisting of position and velocity of the satellite, positions of three ground tracking stations, as well as mu, J2, and drag coefficient for estimating higher order perturbation effects).
 - [X] Test sequential estimation, batch estimation with same epoch measurement for each batch
 - [ ] Implement multiple epoch measurements in each batch
 - [ ] Controls toolbox with basic algorithms (mixed C++ and calls to Python libraries, eventually all C++ for performance improvement)
 - [ ] Add higher order perturbation effects to motion models (tide contribution, drag, third-body effects, solar radiation, Earth radiation, etc)
 - [ ] Testing, bug fixes
 - [ ] Optimize code design for modularity and OOP for easy extensions to other models and simulations
 - [ ] Add fancier satellite simulation as a module with a tutorial describing how to add modules
 - [ ] Add full 6DF module

[//]: # (Image References)

 [GUI]: ./SolverDefinition.png "Solver"
 [Car]: ./Car.png "Car"
 [Orbit]: ./sat.png "Orbit"
 [R3B]: ./Restricted3Body.png "Restricted 3 Body"
 [video1]: ./orbit.mov "Satelite Orbit Video"

#### Restricted 3 body problem - lunar mission

![R3B][R3B]

#### Satellite Tracking

![Orbit][Orbit]


#### Adaptive Cruise Control

![Car][Car]

#### Example of Solver Code

![GUI][GUI]

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
