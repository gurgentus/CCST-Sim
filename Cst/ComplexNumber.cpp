#include "ComplexNumber.hpp"
#include <cmath>

ComplexNumber::ComplexNumber()
{
    m_Re = 0.0;
    m_Im = 0.0;
}

ComplexNumber::ComplexNumber(const ComplexNumber& z)
{
    m_Re = z.m_Re;
    m_Im = z.m_Im;
}

ComplexNumber::ComplexNumber(double mod, double arg)
{
    m_Re = mod;
    m_Im = arg;
}

ComplexNumber::ComplexNumber(double mod, double arg, bool polar)
{
    if (polar == true)
    {
        m_Re = mod*cos(arg);
        m_Im = mod*sin(arg);
    }
    else
    {
        m_Re = mod;
        m_Im = arg;
    }
}

double ComplexNumber::mod() const
{
    return sqrt(m_Re*m_Re+m_Im*m_Im);
}

double ComplexNumber::arg() const
{
    return atan2(m_Im, m_Re);
}

ComplexNumber ComplexNumber::conj() const
{
    ComplexNumber res;
    res.m_Re = m_Re;
    res.m_Im = -m_Im;
    return res;
}

ComplexNumber ComplexNumber::cpow(double n) const
{
    double modulus = mod();
    double argument = arg();
    double pmod = pow(modulus, n);
    double parg = argument*n;
    double resRe = pmod*cos(parg);
    double resIm = pmod*sin(parg);
    ComplexNumber z(resRe, resIm);
    return z;
}

bool ComplexNumber::isReal() const
{
    if (fabs(m_Im) < PRECISION)
    {
        return true;
    }
    else
    {
        return false;
    }
}
double ComplexNumber::getRe() const
{
    return m_Re;
}
double ComplexNumber::getIm() const
{
    return m_Im;
}

ComplexNumber& ComplexNumber::operator=(const ComplexNumber& z)
{
    m_Re = z.m_Re;
    m_Im = z.m_Im;
    return *this;
}

ComplexNumber ComplexNumber::operator-() const
{
    ComplexNumber res;
    res.m_Re = -m_Re;
    res.m_Im = -m_Im;
    return res;
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& z) const
{
    ComplexNumber w;
    w.m_Re = m_Re + z.m_Re;
    w.m_Im = m_Im + z.m_Im;
    return w;
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& z) const
{
    ComplexNumber w;
    w.m_Re = m_Re - z.m_Re;
    w.m_Im = m_Im - z.m_Im;
    return w;
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber& z) const
{
    double modulus = mod();
    double argument = arg();
    double pmod = modulus/z.mod();
    double parg = argument-z.arg();
    double resRe = pmod*cos(parg);
    double resIm = pmod*sin(parg);
    ComplexNumber res(resRe, resIm);
    return res;
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber& z) const
{
    double modulus = mod();
    double argument = arg();
    double pmod = modulus*z.mod();
    double parg = argument+z.arg();
    double resRe = pmod*cos(parg);
    double resIm = pmod*sin(parg);
    ComplexNumber res(resRe, resIm);
    return res;
}

bool ComplexNumber::operator==(const ComplexNumber& z) const
{
    ComplexNumber temp = *this - z;
    if (temp.mod() < 0.0001)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::ostream& operator<<(std::ostream& output, const ComplexNumber& z)
{
    if (z.isReal() == true)
    {
        output << z.m_Re;
    }
    else
    {
        output << "(" << z.m_Re << " ";

        if (z.m_Im >= 0.0)
        {
            output << "+ " << z.m_Im << "i)";
        }
        else
        {
            output << "- " << -z.m_Im << "i)";
        }
    }
    return output;
}
