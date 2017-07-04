#include <cassert>
#include <iostream>
#include <fstream>
#include <math.h>  
#include <vector>
#include <cmath>
#include "TwoBodySolver.hpp"
#include <QApplication>

#include <Python.h>


const double h = 0.1;// (tf-t0)/n;
const double G = 6.67259e-20;
const double m1 = 5.974e24;
const double m2 = 0; //7.348e22;

using namespace std;

void TwoBodySolver::InitialConditions()
{

//    const double mu = G*(m1+m2);
//    const double r = 384400;
//    const double e = 0.0549;
//    const double mom = sqrt(r*mu*(1+e));
//    const double v = mom/r;
    // const double v = sqrt(mu/r);

    Eigen::Vector3d Rx, Vx;

    // if we want to describe the
    /*
    omt.orbit_desc_apog(6700, 10000, 60*M_PI/180, 270*M_PI/180, 45*M_PI/180, 398600);
    Eigen::Vector3d r, v;
    double theta = 230*M_PI/180;
    r << cos(theta), sin(theta), 0;
    r = ((omt.h*omt.h)/(omt.mu*(1+omt.e*cos(theta))))*r;
    v << -sin(theta), omt.e+cos(theta), 0;
    v = (omt.mu/omt.h)*v;

    // position in geocentric equatorial frame
    omt.change_coords(Rx, r);
    omt.change_coords(Vx, v);
    */

    // if we want to describe the trajectory using Gibbs method
    /*

    Omt::orbit_desc(Rx, Vx, QVector3D(-294.32, 4265.1, 5986.7),
                   QVector3D(-1365.5, 3637.6, 6346.8), QVector3D(-2940.3, 2473.7, 6555.8), 398600);
    omt.orbit_desc(QVector3D(Rx(0), Rx(1), Rx(2)), QVector3D(Vx(0), Vx(1), Vx(2)), 398600);
    */

    // if we want to describe the trajectory using Lambert problem formulation
    //Omt::orbit_desc(Rx, Vx, QVector3D(5000, 10000, 2100), QVector3D(-14600, 2500, 7000), 3600, true, 398600);
    //omt.orbit_desc(QVector3D(Rx(0), Rx(1), Rx(2)), QVector3D(Vx(0), Vx(1), Vx(2)), 398600);

    // satellite orbit
    Rx << 757.7, 5222.607, 4851.5;
    Vx << 2.21321, 4.67834, -5.37130;
    InitialConditions(Rx, Vx);
}

void TwoBodySolver::InitialConditions(Eigen::Vector3d r, Eigen::Vector3d v)
{
    RungeKuttaSolver::SetStateDimension(12);
    RungeKuttaSolver::SetStepSize(h);

    state[0] = 0;
    state[1] = 0;
    state[2] = 0;
    state[6] = 0;
    state[7] = 0;
    state[8] = 0;
    state[3] = r(0);
    state[4] = r(1);
    state[5] = r(2);
    state[9] = v(0);
    state[10] = v(1);
    state[11] = v(2);

    SetInitialValue(state);
    //SetTimeInterval(0, 400);
    t_ = 0;
}

//void Simulator::RightHandSide(double t, const std::vector<double> &y, std::vector<double> &f)
//{
//    double r1 = sqrt((y[1]+pi2*r12)*(y[1]+pi2*r12)+y[2]*y[2]);
//    double r2 = sqrt((y[1]-pi1*r12)*(y[1]-pi1*r12)+y[2]*y[2]);

//    double Omega = 0;
//    double mu1 = 1;
//    double mu2 = 1;
//    double r1cube = r1*r1*r1;
//    double r2cube = r2*r2*r2;
//    f[0] = y[3];
//    f[1] = y[4];
//    f[2] = 2*Omega*y[4]+Omega*Omega*y[1]-mu1*(y[1]+pi2*r12)/r1cube-mu2*(y[1]-pi1*r12)/r1cube;
//    f[3] = -2*Omega*y[3]+Omega*Omega*y[2]-mu1*y[2]/r1cube-mu2*y[2]/r2cube;
//}

void TwoBodySolver::RightHandSide(double t, const std::vector<double> &y, std::vector<double> &f)
{
    double r = sqrt(pow(y[3]-y[0],2) + pow(y[4]-y[1],2) + pow(y[5]-y[2],2));
    const double rho_0 = 3.614e-4;
    const double R_e = 6378.1363;
    const double r_0 = 7.0e2+R_e;
    const double H = 88.667;
    const double A = 3e-6;
    const double omega = 2*M_PI/86164;
    double rho = rho_0*exp(-(r-r_0)/H);
    double J2 = 1.082626925638815e-3;
    double C_D = 2;
    const double omega_E = 2*M_PI/86164;
//    double x = y[3];
//    double y = y[4];
//    double z = y[5];
    double u = y[6];
    double v = y[7];
    double w = y[8];
    double v_rel = sqrt((u+omega_E*y[4])*(u+omega_E*y[4])+(v-omega_E*y[3])*(v-omega_E*y[3])+w*w);

    f[0] = y[6];
    f[1] = y[7];
    f[2] = y[8];
    f[3] = y[9];
    f[4] = y[10];
    f[5] = y[11];
    f[6] = G*m2*(y[3]-y[0])/pow(r,3);
    f[7] = G*m2*(y[4]-y[1])/pow(r,3);
    f[8] = G*m2*(y[5]-y[2])/pow(r,3);
    f[9] = -G*m1*(y[3]-y[0])/pow(r,3);// - G*m1*J2*R_e*R_e*y[3]*(1.5/(pow(r,5))-7.5*y[5]/pow(r,7))
          //  -0.5*rho*C_D*A*v_rel*(u + omega_E*y[4])/970;
    f[10] = -G*m1*(y[4]-y[1])/pow(r,3);// - G*m1*J2*R_e*R_e*y[4]*(1.5/(pow(r,5))-7.5*y[5]/pow(r,7))
            //-0.5*rho*C_D*A*v_rel*(v - omega_E*y[3])/970;
    f[11] = -G*m1*(y[5]-y[2])/pow(r,3);// - G*m1*J2*R_e*R_e*y[5]*(1.5/(pow(r,5))-7.5*y[5]/pow(r,7))
           // -0.5*rho*C_D*A*v_rel*w/970;
}

QVector3D TwoBodySolver::position()
{
    double XG;
    double YG;
    double ZG;

    XG = state[3] - state[0]; //(m1*state[0][i] + m2*state[3][i])/(m1+m2);
    YG = state[4] - state[1]; //(m1*state[1][i] + m2*state[4][i])/(m1+m2);
    ZG = state[5] - state[2]; // (m1*state[2][i] + m2*state[5][i])/(m1+m2);

    return QVector3D(XG, YG, ZG);
}

QVector3D TwoBodySolver::velocity()
{
    double U;
    double V;
    double W;

    U = state[9] - state[6];
    V = state[10] - state[7];
    W = state[11] - state[8];

    return QVector3D(U, V, W);
}

double TwoBodySolver::eccentricity()
{
//    QVector3D pos = position();
//    QVector3D vel = velocity();
//    QVector3D h_vec = QVector3D::crossProduct(pos,vel);
//    QVector3D C = QVector3D::crossProduct(vel,h_vec) - mu*pos/pos.length();
//    double e = C.length()/mu;
    return omt.e;
}

//void TwoBodySolver::Simulate()
//{

//    state.reserve(12);
//    state[0] = 0;
//    state[1] = 0;
//    state[2] = 0;
//    state[6] = 10;
//    state[7] = 20;
//    state[8] = 30;
//    state[3] = 3000;
//    state[4] = 0;
//    state[5] = 0;
//    state[9] = 0;
//    state[10] = 40;
//    state[11] = 0;

//    SetInitialValue(state);
//    SetTimeInterval(t0, tf);


    
//    // std::cout << "Enter components of the initial body 1 position vector." << std::endl;
//    // std::cout << "X:" << state[0] << std::endl;
//    // std::cout << "Y:" << state[1] << std::endl;
//    // std::cout << "Z:" << state[2] << std::endl;
    
//    // std::cout << "Enter components of the initial body 1 velocity vector." << std::endl;
//    // std::cout << "X:" << state[6] << std::endl;
//    // std::cout << "Y:" << state[7] << std::endl;
//    // std::cout << "Z:" << state[8] << std::endl;

    
//    // std::cout << "Enter components of the initial body 2position vector." << std::endl;
//    // std::cout << "X:" << state[3] << std::endl;
//    // std::cout << "Y:" << state[4] << std::endl;
//    // std::cout << "Z:" << state[5] << std::endl;
    
//    // std::cout << "Enter components of the initial body 2 velocity vector." << std::endl;
//    // std::cout << "X:" << state[9] << std::endl;
//    // std::cout << "Y:" << state[10] << std::endl;
//    // std::cout << "Z:" << state[11] << std::endl;

//    t_ = t0;

//    std::cout << "Calling Python to find the sum of 2 and 2.\n";
//    // Initialize the Python interpreter.
////    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
////    if (program == NULL) {
////        std::cout << "Fatal error: cannot decode argv[0]\n";
////        exit(1);
////    }
////    Py_SetProgramName(program);


////    QString execFile = QApplication::instance()->applicationFilePath();

////    std::wstring execFile2 = execFile.toStdWString();
////    //std::cout << "T:" << execFile2.c_str();

////    QStringList pythonPath;
////    pythonPath << "/Users/gurgentus/Dropbox/MyOpenGL";
////    QStringList pythonHome;
////    pythonHome << "/Applications/anaconda";
////    //QDir::toNativeSeparators(QFileInfo(QFileInfo(execFile).absoluteDir(), "libpy34.zip").canonicalFilePath());

////    std::wstring pythonPath2 = pythonPath.join(":").toStdWString();
////    std::wstring pythonHome2 = pythonHome.join(":").toStdWString();
////    // Path of our executable
////    Py_SetProgramName((wchar_t*)execFile2.c_str());
////    Py_SetPythonHome((wchar_t*)pythonHome2.c_str());

////    Py_Initialize();

////    // Set module search path
////    PyObject *sys = PyImport_ImportModule("sys");
////    PyObject *path = PyObject_GetAttrString(sys, "path");
////    PyList_Append(path, PyUnicode_FromString("/Users/gurgentus/Dropbox/MyOpenGL"));


////    // Create some Python objects that will later be assigned values.
////    PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;

////    // Convert the file name to a Python string.
////    pName = PyUnicode_DecodeFSDefault("sample");
////    // Import the file as a Python module.
////    pModule = PyImport_Import(pName);
////    if (pModule == nullptr)
////    {
////        PyErr_Print();
////        std::cout << "error";
////        std::exit(1);
////    }

////    Py_DECREF(pName);
////    //if (pModule != NULL) {
////    pFunc = PyObject_GetAttrString(pModule, "add");
////    //}

////    // Create a Python tuple to hold the arguments to the method.
////    pArgs = PyTuple_New(2);
////    // Convert 2 to a Python integer.
////    pValue = PyLong_FromLong(2);
////    // Set the Python int as the first and second arguments to the method.
////    PyTuple_SetItem(pArgs, 0, pValue);
////    PyTuple_SetItem(pArgs, 1, pValue);
////    // Call the function with the arguments.
////    PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
////    // Print a message if calling the method failed.
////    if(pResult == NULL)
////    std::cout << "Calling the add method failed.\n";
////    // Convert the result to a long from a Python object.
////    long result = PyLong_AsLong(pResult);
////    // Destroy the Python interpreter.
////    Py_Finalize();
////    // Print the result.
////    std::cout << "The result is " << result << std::endl;

//        //std::cout  << XG << " " << YG << " " << ZG << std::endl;

////         for (int j = 0; j < 12; j++)
////         {

////             std::cout << state[i][j] << "  ";
////         }
//        //write_output << std::endl;

//    //write_output.close();
//    //return 0;
//}
