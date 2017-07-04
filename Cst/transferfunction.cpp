#include "TransferFunction.hpp"
#include <string>
#include <cmath>
#include <sstream>

TransferFunction::TransferFunction()
{

}

TransferFunction::TransferFunction(const TransferFunction& tf)
{
    numerator = tf.numerator;
    denominator = tf.denominator;
}

TransferFunction::TransferFunction(std::vector<ComplexNumber> n, std::vector<ComplexNumber> d)
{
    numerator = n;
    denominator = d;

}

TransferFunction::TransferFunction(std::vector<double> n, std::vector<double> d)
{
    std::vector<ComplexNumber> nC;
    for (std::vector<double>::iterator it = n.begin(); it != n.end(); ++it)
    {
        nC.push_back(ComplexNumber(*it,0));
    }
    std::vector<ComplexNumber> dC;
    for (std::vector<double>::iterator it = d.begin(); it != d.end(); ++it)
    {
        dC.push_back(ComplexNumber(*it,0));
    }
    numerator = nC;
    denominator = dC;
}

TransferFunction TransferFunction::operator/(const TransferFunction& ttf2) const
{
    TransferFunction tf1;
    if (denominator == ttf2.denominator)
    {
        tf1.numerator = numerator;
        tf1.denominator = ttf2.numerator;
        return tf1;
    }
    else
    {
        tf1.numerator = ttf2.denominator;
        tf1.denominator = ttf2.numerator;
        //std::cout << tf1 << std::endl;
        //std::cout << "T: " << *this << std::endl;
        //TransferFunction tfr(TransferFunction({1},{1}) * tf1);
        return *this * tf1;
    }
}

void TransferFunction::reduce()
{

    std::vector<ComplexNumber> numZeros;
    std::vector<ComplexNumber> denomZeros;

    TransferFunction tf({this->numerator[0]}, {this->denominator[0]});

    zeros(numerator, numZeros);
    zeros(denominator, denomZeros);


    for (std::vector<ComplexNumber>::iterator it = denomZeros.begin(); it != denomZeros.end();)
    {
        if(std::find(numZeros.begin(), numZeros.end(), *it) != numZeros.end())
        {
            /* numerator has this zero */
            numZeros.erase(std::find(numZeros.begin(), numZeros.end(), *it));
            denomZeros.erase(it);
        }
        else
        {
            ++it;
        }
    }



    for (std::vector<ComplexNumber>::iterator it = numZeros.begin(); it != numZeros.end(); ++it)
    {
        tf = tf*TransferFunction({ComplexNumber(1,0), -*it}, {ComplexNumber(1,0)} );
    }
    for (std::vector<ComplexNumber>::iterator it = denomZeros.begin(); it != denomZeros.end(); ++it)
    {
        tf = tf*TransferFunction({ComplexNumber(1,0)}, {ComplexNumber(1,0), -*it});
    }


    numerator = tf.numerator;
    denominator = tf.denominator;
}

TransferFunction TransferFunction::operator*(const TransferFunction& tf2) const
{
    unsigned long order = (int)(this->numerator.size()+tf2.numerator.size()-1);
    TransferFunction w;
    w.numerator.reserve(order);

    for (unsigned long i=0; i<order; ++i)
    {
       w.numerator.push_back(ComplexNumber(0,0));
    }
    for (unsigned long i=0; i< numerator.size(); ++i)
    {
        for (unsigned long j=0; j< tf2.numerator.size(); ++j)
        {
            w.numerator[i+j] = w.numerator[i+j] + numerator[i]*tf2.numerator[j];
        }
    }
    order = (int)(this->denominator.size()+tf2.denominator.size()-1);
    w.denominator.reserve(order);
    for (unsigned long i=0; i<order; ++i)
    {
       w.denominator.push_back(ComplexNumber(0,0));
    }
    for (unsigned long i=0; i< denominator.size(); ++i)
    {
        for (unsigned long j=0; j< tf2.denominator.size(); ++j)
        {
            w.denominator[i+j] =  w.denominator[i+j] + denominator[i]*tf2.denominator[j];
        }
    }

    return w;
}

TransferFunction TransferFunction::operator+(const TransferFunction& ttf) const
{
    TransferFunction tf1(*this * TransferFunction(ttf.denominator, ttf.denominator));
    TransferFunction tf2(ttf * TransferFunction(denominator, denominator));
    TransferFunction w;
    unsigned long order = tf1.numerator.size();
    if (tf2.numerator.size() > order)
    {
        order = tf2.numerator.size();
        w.numerator.resize(order);
        for (int i=order-1; i>=0; i--)
        {
           w.numerator[i]= tf2.numerator[i];
           if (i >= (int)order - (int)tf1.numerator.size())
           {
               w.numerator[i] = w.numerator[i] + tf1.numerator[(int)tf1.numerator.size()-(order-i)];
           }
        }
    }
    else
    {
        w.numerator.resize(order);
        for (int i=order-1; i>=0; i--)
        {
           w.numerator[i] = tf1.numerator[i];
           if (i >= (int)order - (int)tf2.numerator.size())
           {
               w.numerator[i] = w.numerator[i] + tf2.numerator[(int)tf2.numerator.size()-(order-i)];
           }
        }
    }
    w.denominator = tf1.denominator;

    return w;
}

void TransferFunction::poles(std::vector<ComplexNumber>& roots)
{
    std::vector<ComplexNumber> numZeros;

    zeros(denominator, roots);
    zeros(numerator, numZeros);

    for (std::vector<ComplexNumber>::iterator it = roots.begin(); it != roots.end(); ++it)
    {
        if(std::find(numZeros.begin(), numZeros.end(), *it) != numZeros.end())
        {
            /* numerator has this zero */
            numZeros.erase(std::find(numZeros.begin(), numZeros.end(), *it));
            roots.erase(it);
        }
    }

}

void TransferFunction::pfd(Pfd& pfd)
{
    std::vector<ComplexNumber> polesVector;
    std::vector<ComplexNumber> pdfNum;
    pfd.reset();
    poles(polesVector);
    //std::cout << "NUMVE: " << polesVector.size();
    for (std::vector<ComplexNumber>::iterator it = polesVector.begin(); it != polesVector.end();)
    {
        ComplexNumber cur(*it);
        int multiplicity = 1;
        std::vector<ComplexNumber>::iterator it2 = std::find (polesVector.begin(), polesVector.end(), cur);
        while ( it2 != polesVector.end())
        {

            it2 = std::find(polesVector.begin(), polesVector.end(), cur);

            polesVector.erase(it2);

            if (std::find (polesVector.begin(), polesVector.end(), cur) != polesVector.end())
            {
                ++multiplicity;
            }
            else
            {
                TransferFunction mult({ComplexNumber(1,0), -cur}, {ComplexNumber(1,0)});
                TransferFunction resCalc(*this);

                for (int i=0; i< multiplicity; ++i)
                {
                   resCalc = resCalc * mult;
                }

                for (int i=0; i< multiplicity; ++i)
                {
                    resCalc.reduce();
                                        //std::cout << resCalc << std::endl;
                    if (i > 0)
                    {
                        resCalc = resCalc.deriv();
                    }
                    ComplexNumber pdfNum(resCalc.evaluate(cur));

                    pfd.addToPfd(pdfNum.getRe(), 0, cur.getRe(), 0, multiplicity-i);
                    it2 = polesVector.end();
                }

                multiplicity = 1;
            }

        }


    }

}

TransferFunction TransferFunction::deriv()
{
    std::vector<ComplexNumber> numDeriv;
    std::vector<ComplexNumber> denomDeriv;

    deriv(numerator, numDeriv );
    deriv(denominator, denomDeriv);
    TransferFunction w1(TransferFunction(denomDeriv, {ComplexNumber(1,0)})*TransferFunction(numerator, {ComplexNumber(1,0)}));
    TransferFunction w2(TransferFunction(numDeriv, {ComplexNumber(1,0)})*TransferFunction(denominator, {ComplexNumber(1,0)}));

    TransferFunction w(w2+(-w1));
    w = w/(TransferFunction(denominator, {ComplexNumber(1,0)})*TransferFunction(denominator, {ComplexNumber(1,0)}));

    return w;
}

TransferFunction TransferFunction::operator-() const
{
    TransferFunction w({ComplexNumber(-1,0)}, {ComplexNumber(1,0)});
    return *this*w;
}

ComplexNumber TransferFunction::evaluate(ComplexNumber& pt)
{
    //std::cout << evaluatePolynomial(numerator, pt)/evaluatePolynomial(denominator, pt) << std::endl;
    return evaluatePolynomial(numerator, pt)/evaluatePolynomial(denominator, pt);
}

ComplexNumber TransferFunction::evaluatePolynomial(std::vector<ComplexNumber> coeffs, ComplexNumber& pt)
{
    ComplexNumber rValue(0.0, 0.0);
    for (unsigned long i=0; i<coeffs.size(); ++i)
    {
       rValue = rValue + coeffs[i]*pt.cpow(coeffs.size()-i-1);
    }
    return rValue;
}

void TransferFunction::deriv(std::vector<ComplexNumber> coeffs, std::vector<ComplexNumber>& deriv)
{
    unsigned long order = coeffs.size();
    for (unsigned long i=2; i<=order; ++i)
    {
       deriv.push_back(ComplexNumber(0,0));
    }
    for (unsigned long i=2; i<=order; ++i)
    {
       deriv[order-i] = coeffs[order-i]*ComplexNumber(i-1,0);
    }
}

void TransferFunction::zeros(std::vector<ComplexNumber> coeffs, std::vector<ComplexNumber>& zeros)
{
    unsigned long order = coeffs.size();
    std::vector<ComplexNumber> deriv;
    deriv.reserve(order-1);

    std::vector<ComplexNumber> updatedZeros;

    for (unsigned long i=2; i<=order; ++i)
    {
       deriv.push_back(ComplexNumber(0,0));
    }
    for (unsigned long i=2; i<=order; ++i)
    {
       deriv[order-i] = coeffs[order-i]*ComplexNumber(i-1,0);
    }

    // initial guesses
    double max = 0;
    for (unsigned long i=0; i<coeffs.size(); ++i)
    {
       max += coeffs[i].mod();
    }

    for (unsigned long i=0; i<order-1; ++i)
    {
       zeros.push_back(ComplexNumber(max/2, i*6.28/(order-1), true));
       updatedZeros.push_back(ComplexNumber(max/2, i*6.28/(order-1), true));
    }
    bool stop = false;
    for (int iter = 0; iter < NUMITER; iter++)
    {
        stop = true;
        for (unsigned long i=0; i<order-1; i++)
        {
           ComplexNumber temp(evaluatePolynomial(coeffs, zeros[i])/evaluatePolynomial(deriv, zeros[i]));
           ComplexNumber denomSum(0.0, 0.0);

           for (unsigned long k=0; k<order-1; k++)
           {
               if (k != i)
               {
                   denomSum = denomSum + ComplexNumber(1,0)/(zeros[i]-zeros[k]);
               }

           }
           denomSum = ComplexNumber(1,0) - temp*denomSum;
           updatedZeros[i] = zeros[i] -temp/denomSum;

        }
        for (unsigned long i=0; i<order-1; i++)
        {
            zeros[i] = updatedZeros[i];
            if (evaluatePolynomial(deriv, zeros[i]).mod() > PRECISION)
            {
                stop = false;
            }
        }

        if (stop == true)
        {
            iter = NUMITER;
        }

    }
}


//overloading the insertion << operator
std::ostream& operator<<(std::ostream& output, const TransferFunction& tf)
{
    std::string numstream("");
    std::string denomstream("");

    output << std::endl;
    unsigned long power = tf.numerator.size() - 1;
    for (std::vector<const ComplexNumber>::iterator it = tf.numerator.begin(); it != tf.numerator.end(); ++it)
    {
        if (it->isReal())
        {
            double real_part = it->getRe();

            if (real_part != 0)
            {
                if (real_part < 0)
                {
                    //numstream += "-";
                }
                if (real_part > 0 && power != tf.numerator.size() - 1)
                {
                    numstream += "+";
                }

                if ((real_part != -1 && real_part != 1) || (power == 0))
                {
                    numstream += std::to_string(real_part);
                }
            }
        }
        else
        {
            if (power != tf.numerator.size() - 1)
            {
                numstream += "+";
            }
            std::ostringstream stream;
            stream << *it;
            numstream = numstream + stream.str();
        }

        if (power == 1)
        {
            numstream += "s";
        }
        else
        {
            if (power != 0)
            {
                numstream += "s^" + std::to_string(power);
            }
        }

        --power;
    }

    power = tf.denominator.size() - 1;
    for (std::vector<const ComplexNumber>::iterator it = tf.denominator.begin(); it != tf.denominator.end(); ++it)
    {
        if (it->isReal())
        {
            double real_part = it->getRe();

            if (real_part != 0)
            {
                if (real_part < 0)
                {
                    //denomstream += "-";
                }
                if (real_part > 0 && power != tf.denominator.size() - 1)
                {
                    denomstream += "+";
                }

                if ((real_part != -1 && real_part != 1) || (power == 0))
                {
                    denomstream += std::to_string(real_part);
                }
            }
        }
        else
        {
            if (power != tf.denominator.size() - 1)
            {
                denomstream += "+";
            }
            std::ostringstream stream;
            stream << *it;
            denomstream = denomstream + stream.str();
        }
        if (power == 1)
        {
            denomstream += "s";
        }
        else
        {
            if (power != 0)
            {
                denomstream += "s^" + std::to_string(power);
            }
        }

        --power;
    }

    unsigned long size = numstream.length();
    if (denomstream.length() > numstream.length())
    {
        size = denomstream.length();
    }
    output << std::endl;
    if (numstream.length() < denomstream.length())
    {
        for (unsigned long i = 0; i< (denomstream.length() - numstream.length())/2; ++i )
        {
            output << " ";
        }
    }
    output << numstream;
    output << std::endl;
    for (unsigned long i=0; i<= size; ++i)
    {
        output << "-";
    }
    output << std::endl;
    if (denomstream.length() < numstream.length())
    {
        for (unsigned long i = 0; i< (numstream.length() - denomstream.length())/2; ++i )
        {
            output << " ";
        }
    }
    output << denomstream;
    output << std::endl;

    return output;

}
