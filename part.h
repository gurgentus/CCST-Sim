#ifndef PART_H
#define PART_H

#include "sbody.h"
#include "mesh.h"


class Part : public SBody, public Mesh
{
public:
    Part();
    ~Part();
    bool setupDefaultMesh();
    void initializeControls();
    void updateControls();
};

#endif // PART_H
