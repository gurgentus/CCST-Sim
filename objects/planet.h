#ifndef PLANET_H
#define PLANET_H

#include "vertex.h"
#include "mesh.h"
#include "textures.h"
#include "sbody.h"

class Planet : public Mesh, public SBody
{
public:
    Planet();
    bool SetupDefaultMesh(QVector4D texSignature = QVector4D( 0.0f, 1.0f, 0.0f, 1.0f ));

    // initialize state and control values
    void InitializeState();
    void InitializeControls();
    // update state based on gui control
    void UpdateControls();

    double r() const;
    void setR(double r);

    double xRot;
    double yRot;
    double zRot;

    void setPosition(QVector3D pos);
    void UpdateState(double dt);
protected:
    void ResetOrientation();

    // simulation speed control
    Control* speedControl;
    double sim_speed_;
    double x_;
    double y_;
    double z_;
    double r_;


};

#endif // PLANET_H
