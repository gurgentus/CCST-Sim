#ifndef PFD_H
#define PFD_H

#include <vector>

struct pfdFraction {
  double r1,r2; //numerator
  double c,d; //denominator
  int multiplicity; // note when multiplicity is 1, r2=0, d=0;
} ;

class Pfd
{
private:
    std::vector<pfdFraction> decomp;
    int factorial(int n);


public:
    Pfd();
    void reset();
    void addToPfd(double r_1, double r_2, double c, double d, int multiplicity);
    void printInverseLaplaceTransform();
    double evaluateInverseLaplaceTransform(double t);
    friend std::ostream& operator<<(std::ostream& output, const Pfd& pfd);

};

#endif // PFD_H
