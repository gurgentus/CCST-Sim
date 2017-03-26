#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include <vector>
#include <iostream>
#include "complexnumber.h"
#include "pfd.h"

#define NUMITER 100

class TransferFunction
{
private:
    std::vector<ComplexNumber> numerator;
    std::vector<ComplexNumber> denominator;
public:
    TransferFunction();
    TransferFunction(const TransferFunction& tf);
    TransferFunction(std::vector<ComplexNumber> n, std::vector<ComplexNumber> d);
    TransferFunction(std::vector<double> n, std::vector<double> d);
    TransferFunction operator*(const TransferFunction& tf2) const;
    TransferFunction operator/(const TransferFunction& tf2) const;
    TransferFunction operator+(const TransferFunction& tf2) const;
    TransferFunction operator-() const;

    friend std::ostream& operator<<(std::ostream& output, const TransferFunction& tf);

    void poles(std::vector<ComplexNumber> &roots);
    void reduce();
    void pfd(Pfd &pfd);
    void deriv(std::vector<ComplexNumber> coeffs, std::vector<ComplexNumber>& deriv);
    TransferFunction deriv();
    ComplexNumber evaluate(ComplexNumber& pt);
    ComplexNumber evaluatePolynomial(std::vector<ComplexNumber> coeffs, ComplexNumber& pt);
    void zeros(std::vector<ComplexNumber> coeffs, std::vector<ComplexNumber> &zeros);

};

#endif // TRANSFERFUNCTION_H
