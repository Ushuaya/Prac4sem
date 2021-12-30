#ifndef Tri
#define Tri
#include "Exeption.h"
#include "Figure.h"



class Triangle: virtual public Figure {
protected:
    double a, b, c;
public:
    Triangle(double x1 = 1, double x2 = 1, double x3 = 1)
    {
        if (x1 < 0 || x2 < 0 || x3 < 0)
            throw Exeption(3);
        a = x1;
        b = x2;
        c = x3;
    }
    double Volume();
    double Square();
    
};





#endif
