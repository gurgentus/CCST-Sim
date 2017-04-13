#ifndef PART_H
#define PART_H

#include "sbody.h"
#include "mesh.h"


class Part : public SBody, public Mesh
{
public:
    Part();
    ~Part();
    bool SetupDefaultMesh();
    void InitializeControls();
    void UpdateControls();
};

#endif // PART_H
