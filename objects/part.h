#ifndef PART_H
#define PART_H

#include "sbody.h"
#include "mesh.h"


class Part : public SBody, public Mesh
{
public:
    Part();
    ~Part();
    bool SetupDefaultMesh(QVector4D texSignature);
    void InitializeControls();
    void UpdateControls();
};

#endif // PART_H
