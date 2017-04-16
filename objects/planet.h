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
    void InitializeOutputs();
    // update state and output based on gui control
    void UpdateControls();
    void UpdateOutputs();

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

    // define outputs to be displayed
    Output* x_position_output_;
    Output* y_position_output_;
    Output* z_position_output_;
};

#endif // PLANET_H
