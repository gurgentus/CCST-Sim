#ifndef PLANET_H
#define PLANET_H

#include <common/vertex.h>
#include <objects/mesh.h>
#include <common/textures.h>
#include <objects/sbody.h>
#include <nums/AbstractOdeSolver.hpp>

class Planet : public Mesh, public SBody
{
public:
    Planet();
    bool SetupDefaultMesh(QVector4D texSignature = QVector4D( 0.0f, 1.0f, 0.0f, 1.0f ));

    // initialize state and control values
    void InitializeState();
    void InitializeOutputs();
    // update state and output based on gui control
    void UpdateOutputs();

    void SetPositionFunction( QVector3D (AbstractOdeSolver::*fun)()  );
    void SetRotationFunction( double (AbstractOdeSolver::*fun)()  );

    double r() const;
    void setR(double r);

    double xRot;
    double yRot;
    double zRot;

    void setPosition(QVector3D pos);
    void UpdateState(double dt);

    // Pointers to two functions returning respectively position and rotation of the object
    // These can be set to any functions of the corresponding solver
    QVector3D (AbstractOdeSolver::*pos)();
    double (AbstractOdeSolver::*rot)();
protected:
    void ResetOrientation();

    double x_;
    double y_;
    double z_;
    double u_;
    double v_;
    double w_;
    double r_;

    // define outputs to be displayed
    Output* x_position_output_;
    Output* y_position_output_;
    Output* z_position_output_;
    Output* r_output_;
    Output* t_output_;
};

#endif // PLANET_H
