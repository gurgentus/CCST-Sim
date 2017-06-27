#ifndef PART_H
#define PART_H

#include "SimObject.hpp"
#include "Mesh.hpp"


class Part : public SimObject, public Mesh
{
public:
    Part();
    ~Part();
    bool SetupDefaultMesh(QVector4D texSignature);
    void InitializeControls();
    void UpdateControls();
};

#endif // PART_H
