#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#define PRECISION 0.000001

#include <iostream>

// ComplexNumber - ref: Guide to Scientific Computing in C++, J. Pitt-Francis, J. Whiteley
class ComplexNumber
{
private:
    double m_Re;
    double m_Im;
public:
    ComplexNumber();
    ComplexNumber(const ComplexNumber& z);
    ComplexNumber(double Re, double Im);
    ComplexNumber(double mod, double arg, bool polar);
    double mod() const;
    double arg() const;
    ComplexNumber conj() const;
    ComplexNumber cpow(double n) const;
    bool isReal() const;
    double getRe() const;
    double getIm() const;
    ComplexNumber& operator=(const ComplexNumber& z);
    ComplexNumber operator-() const;
    ComplexNumber operator+(const ComplexNumber& z) const;
    ComplexNumber operator-(const ComplexNumber& z) const;
    ComplexNumber operator*(const ComplexNumber& z) const;
    ComplexNumber operator/(const ComplexNumber& z) const;
    bool operator==(const ComplexNumber& z) const;
    friend std::ostream& operator<<(std::ostream& output, const ComplexNumber& z);
};

#endif // COMPLEXNUMBER_H
