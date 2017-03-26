#include "pfd.h"
#include <sstream>
#include <cmath>
#include <iostream>

Pfd::Pfd()
{

}

void Pfd::reset()
{
    decomp.clear();
}

void Pfd::addToPfd(double r_1, double r_2, double c, double d, int multiplicity)
{
    pfdFraction mPfdFraction;
    mPfdFraction.r1 = r_1;
    mPfdFraction.r2 = r_2;
    mPfdFraction.c = c;
    mPfdFraction.d = d;
    mPfdFraction.multiplicity = multiplicity;
    decomp.push_back(mPfdFraction);
}

void Pfd::printInverseLaplaceTransform()
{
    for (std::vector<const pfdFraction>::iterator it = decomp.begin(); it != decomp.end(); ++it)
    {
       if (it->multiplicity == 1)
       {
        std::cout << it->r1 << "e^(" << it->c << "t)";
       }
       else
       {
           std::cout << it->r1/(factorial(it->multiplicity-1)) << "t^(" << (it->multiplicity-1) << ") e^(" << it->c << "t)";
       }
       if (std::next(it) != decomp.end())
       {
           std::cout << " + ";
       }
       else
       {
           std::cout << std::endl;
       }
    }
}

double Pfd::evaluateInverseLaplaceTransform(double t)
{
    double output = 0;
    for (std::vector<const pfdFraction>::iterator it = decomp.begin(); it != decomp.end(); ++it)
    {
       if (it->multiplicity == 1)
       {
        output = output + it->r1 * exp(it->c*t);
       }
       else
       {
           output = output + it->r1/(factorial(it->multiplicity-1)) * pow(t, it->multiplicity-1) * exp(it->c*t);
       }

    }
    return output;
}

int Pfd::factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

//overloading the insertion << operator
std::ostream& operator<<(std::ostream& output, const Pfd& pfd)
{
    output << std::endl;

    for (std::vector<const pfdFraction>::iterator it = pfd.decomp.begin(); it != pfd.decomp.end(); ++it)
    {
       output << it->r1 << " / " << "(s - " << it->c << ")^" << it->multiplicity;
       if (std::next(it) != pfd.decomp.end())
       {
           output << " + ";
       }
       else
       {
           output << std::endl;
       }
    }
    return output;
}
