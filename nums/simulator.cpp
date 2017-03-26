#include <cassert>
#include <iostream>
#include <fstream>
#include <math.h>  
#include <vector>
#include <cmath>
#include "simulator.h"
#include <QApplication>
#include "RungeKuttaSolver.hpp"
#include <Python.h>

const int n = 20000;
const double G = 6.67259e-20;
const double m1 = 1e26;
const double m2 = 1e26;
const double t0 = 0;
const double tf = 480;
const double h = (tf-t0)/n;

using namespace std;

void Simulator::simulate(vector<QVector3D> &results)
{
    //std::cout << "Hello World!" << std::endl;
    
    //std::ofstream write_output("data.txt");
    //assert(write_output.is_open());

    std::vector<double> state;

    //double f[n][12];
    double XG;
    double YG;
    double ZG;

    state.reserve(12);
    state[0] = 0;
    state[1] = 0;
    state[2] = 0;
    state[6] = 10;
    state[7] = 20;
    state[8] = 30;
    state[3] = 3000;
    state[4] = 0;
    state[5] = 0;
    state[9] = 0;
    state[10] = 40;
    state[11] = 0;

    RungeKuttaSolver rk;
    rk.SetStepSize(h);
    rk.SetInitialValue(state);
    rk.SetTimeInterval(t0, tf);


    
    // std::cout << "Enter components of the initial body 1 position vector." << std::endl;
    // std::cout << "X:" << state[0] << std::endl;
    // std::cout << "Y:" << state[1] << std::endl;
    // std::cout << "Z:" << state[2] << std::endl;
    
    // std::cout << "Enter components of the initial body 1 velocity vector." << std::endl;
    // std::cout << "X:" << state[6] << std::endl;
    // std::cout << "Y:" << state[7] << std::endl;
    // std::cout << "Z:" << state[8] << std::endl;

    
    // std::cout << "Enter components of the initial body 2position vector." << std::endl;
    // std::cout << "X:" << state[3] << std::endl;
    // std::cout << "Y:" << state[4] << std::endl;
    // std::cout << "Z:" << state[5] << std::endl;
    
    // std::cout << "Enter components of the initial body 2 velocity vector." << std::endl;
    // std::cout << "X:" << state[9] << std::endl;
    // std::cout << "Y:" << state[10] << std::endl;
    // std::cout << "Z:" << state[11] << std::endl;

    double t = t0;

    std::cout << "Calling Python to find the sum of 2 and 2.\n";
    // Initialize the Python interpreter.
//    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
//    if (program == NULL) {
//        std::cout << "Fatal error: cannot decode argv[0]\n";
//        exit(1);
//    }
//    Py_SetProgramName(program);


//    QString execFile = QApplication::instance()->applicationFilePath();

//    std::wstring execFile2 = execFile.toStdWString();
//    //std::cout << "T:" << execFile2.c_str();

//    QStringList pythonPath;
//    pythonPath << "/Users/gurgentus/Dropbox/MyOpenGL";
//    QStringList pythonHome;
//    pythonHome << "/Applications/anaconda";
//    //QDir::toNativeSeparators(QFileInfo(QFileInfo(execFile).absoluteDir(), "libpy34.zip").canonicalFilePath());

//    std::wstring pythonPath2 = pythonPath.join(":").toStdWString();
//    std::wstring pythonHome2 = pythonHome.join(":").toStdWString();
//    // Path of our executable
//    Py_SetProgramName((wchar_t*)execFile2.c_str());
//    Py_SetPythonHome((wchar_t*)pythonHome2.c_str());

//    Py_Initialize();

//    // Set module search path
//    PyObject *sys = PyImport_ImportModule("sys");
//    PyObject *path = PyObject_GetAttrString(sys, "path");
//    PyList_Append(path, PyUnicode_FromString("/Users/gurgentus/Dropbox/MyOpenGL"));


//    // Create some Python objects that will later be assigned values.
//    PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;

//    // Convert the file name to a Python string.
//    pName = PyUnicode_DecodeFSDefault("sample");
//    // Import the file as a Python module.
//    pModule = PyImport_Import(pName);
//    if (pModule == nullptr)
//    {
//        PyErr_Print();
//        std::cout << "error";
//        std::exit(1);
//    }

//    Py_DECREF(pName);
//    //if (pModule != NULL) {
//    pFunc = PyObject_GetAttrString(pModule, "add");
//    //}

//    // Create a Python tuple to hold the arguments to the method.
//    pArgs = PyTuple_New(2);
//    // Convert 2 to a Python integer.
//    pValue = PyLong_FromLong(2);
//    // Set the Python int as the first and second arguments to the method.
//    PyTuple_SetItem(pArgs, 0, pValue);
//    PyTuple_SetItem(pArgs, 1, pValue);
//    // Call the function with the arguments.
//    PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
//    // Print a message if calling the method failed.
//    if(pResult == NULL)
//    std::cout << "Calling the add method failed.\n";
//    // Convert the result to a long from a Python object.
//    long result = PyLong_AsLong(pResult);
//    // Destroy the Python interpreter.
//    Py_Finalize();
//    // Print the result.
//    std::cout << "The result is " << result << std::endl;

    for (int i = 0; i < n-1; i++)
    {

        rk.RKIteration(t, state);
        t = t + h;

//        double r = sqrt(pow(state[i][3]-state[i][0],2) + pow(state[i][4]-state[i][1],2) + pow(state[i][5]-state[i][2],2));

//        f[i][0] = state[i][6];
//        f[i][1] = state[i][7];
//        f[i][2] = state[i][8];
//        f[i][3] = state[i][9];
//        f[i][4] = state[i][10];
//        f[i][5] = state[i][11];
//        f[i][6] = G*m2*(state[i][3]-state[i][0])/pow(r,3);
//        f[i][7] = G*m2*(state[i][4]-state[i][1])/pow(r,3);
//        f[i][8] = G*m2*(state[i][5]-state[i][2])/pow(r,3);
//        f[i][9] = -G*m1*(state[i][3]-state[i][0])/pow(r,3);
//        f[i][10] = -G*m1*(state[i][4]-state[i][1])/pow(r,3);
//        f[i][11] = -G*m1*(state[i][5]-state[i][2])/pow(r,3);

//        for (int j = 0; j < 12; j++)
//        {
//            state[i+1][j] = state[i][j] + h * f[i][j];
//        }
//                //std::cout <<  m1 << " " << state[11][i] << " " <<  f[11][i] * h << " " << state[11][i+1] << std::endl;



        XG = state[3] - state[0]; //(m1*state[0][i] + m2*state[3][i])/(m1+m2);
        YG = state[4] - state[1]; //(m1*state[1][i] + m2*state[4][i])/(m1+m2);
        ZG = state[5] - state[2]; // (m1*state[2][i] + m2*state[5][i])/(m1+m2);

        results.push_back(QVector3D(XG, YG, ZG)/100);

        //std::cout  << XG << " " << YG << " " << ZG << std::endl;

//         for (int j = 0; j < 12; j++)
//         {

//             std::cout << state[i][j] << "  ";
//         }
        //write_output << std::endl;


    }
    //write_output.close();
    //return 0;
}
