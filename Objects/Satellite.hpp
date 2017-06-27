#ifndef PLANET_H
#define PLANET_H

#include "Common/Vertex.hpp"
#include "Common/Textures.hpp"
#include "Objects/Mesh.hpp"
#include "Objects/SimObject.hpp"
#include "Nums/AbstractOdeSolver.hpp"

class Satellite : public Mesh, public SimObject
{
public:
    Satellite();
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

    double xRot=0;
    double yRot=0;
    double zRot=0;

    void setPosition(QVector3D pos);
    void UpdateState(double dt);

    // Pointers to two functions returning respectively position and rotation of the object
    // These can be set to any functions of the corresponding solver
    QVector3D (AbstractOdeSolver::*pos)();
    double (AbstractOdeSolver::*rot)();
protected:
    void ResetOrientation();

    double x_=0;
    double y_=0;
    double z_=0;
    double u_=0;
    double v_=0;
    double w_=0;
    double r_=1;

    // define outputs to be displayed
    Output* x_position_output_;
    Output* y_position_output_;
    Output* z_position_output_;
    Output* r_output_;
    Output* t_output_;
};

#endif // PLANET_H
