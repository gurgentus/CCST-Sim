The following tutorials were used for OpenGL functionality
http://www.trentreed.net/blog/qt5-opengl-part-1-basic-rendering/
https://github.com/morgan3d/misc/blob/master/terrain/Terrain.cpp


Adding python interfaces

add in the pro file (add through right-click on the project -> Add Library)


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Applications/anaconda/lib/release/ -lpython3.5m
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Applications/anaconda/lib/debug/ -lpython3.5m
else:unix: LIBS += -L$$PWD/../../../../Applications/anaconda/lib/ -lpython3.5m

INCLUDEPATH += $$PWD/../../../../Applications/anaconda/include/python3.5m
DEPENDPATH += $$PWD/../../../../Applications/anaconda/include/python3.5m
CONFIG += no_keywords

- had to rename libJPEG.dylib; libTIFF.dylib; libPng.dylib; libsqlite3.0.dylib to avoid linker confusion