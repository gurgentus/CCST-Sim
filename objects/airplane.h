#ifndef AIRPLANE_H
#define AIRPLANE_H

#include "mesh.h"

class Airplane : public Mesh
{
public:
    Airplane();
    bool SetupDefaultMesh(QVector4D texSignature = QVector4D( 0.0f, 1.0f, 0.0f, 1.0f ));
private:
    void setupCapMesh();
    void setupSphereMesh();
    void setupFuselageMesh();
};

#endif // AIRPLANE_H
