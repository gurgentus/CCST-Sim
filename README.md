# Generic Estimation Learning Control Simulator

Simulator for testing state estimation (Kalman Filter, Extended Kalman Filter, Unscented Kalman Filter, etc), Machine Learning (classical, deep learning, etc), and Control (classical, optimal, robust, adaptive)  algorithms on general models.  For speed and flexibility rather than using a game engine like Unity or Unreal, I decided to directly use modern OpenGL with OpenGL Shading Language with a light Qt wrapper.  The GUI is also done in Qt for platform independence.


# TODO

 - [X] Basic Qt GUI setup
 - [X] Basic modular OOP framework setup with OpenGL wrappers for 3D graphics
 - [X] Basic car module with PID control algorithm and adaptive cruise control
 - [X] More realistic car model with steering
 - [X] Toy two body and restricted three body (moon mission) orbital mechanics simulations
 - [ ] Controls toolbox with basic algorithms (mixed C++ and calls to Python libraries, eventually all C++ for performance improvement)
 - [ ] Testing, bug fixes
 - [ ] Optimize code design for modularity and OOP for easy extensions to other models and simulations
 - [ ] Add fancier satellite simulation as a module with a tutorial describing how to add modules
 - [ ] Add full 6DF module

[//]: # (Image References)

 [GUI]: ./GUI.png "GUI"
 [Car]: ./Car.png "Car"
 [Orbit]: ./Orbit.png "Orbit"
 [R3B]: ./Restricted3Body.png "Restricted 3 Body"

![Car][Car]

![R3B][R3B]

![Orbit][Orbit]

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
