#include <iostream>
#include "AbstractOdeSolver.hpp"
#include "ForwardEulerSolver.hpp"
#include "RungeKuttaSolver.hpp"

//int main() {
//    // RungeKuttaSolver fSolver;
//    // fSolver.SetStepSize(0.001);
//    // fSolver.SetTimeInterval(0, 1);
//    // fSolver.SetInitialValue(2);
//    // fSolver.SolveEquation();
//    // std::cout << "Hello World!" << std::endl;
    
//    int i = 5;
//    int* p_j = &i;
//    std::cout << *p_j * 5 << std::endl;
    
//    int* p_k = new int;
//    *p_k = *p_j;
    
//    std::cout << *p_k << std::endl;
    
//    int m = 2;
//    int l =4;
    
//    int* p_m = &m;
//    int* p_l = &l;
//    int* p_temp = p_k;
    
//    p_temp = p_m;
//    p_m = p_l;
//    p_l = p_temp;
    
//    std::cout << *p_m << " " << *p_l << std::endl;
    
//    double* x;
//    double* y;
    
//    double sum = 0;
//    for (int k=0; k< 1000000000; k++)
//    {
//        x = new double[3];
//        y = new double[3];
//        for (int i=0; i<3; i++)
//        {
//            x[i] = ((double)(i));
//            y[i] = 4;
//        }
//        for (int i=0; i<3; i++)
//        {
//            sum = sum + x[i]*y[i];
//        }
        
//        delete[] x;
//        delete[] y;
//    }
//    std::cout << sum << std::endl;
//    return 0;
//}
