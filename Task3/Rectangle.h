#ifndef Rec
#define Rec
#include "Exeption.h"
#include "Figure.h"


class Rectangle: virtual public Figure {
protected:
    double a, b;
public:
    Rectangle (double x = 1, double y = 1)
    {
        if (x < 0 || y < 0)
            throw Exeption(1);
        a = x;
        b = y;
    }
    double Volume();
    double Square();
   
};


#endif
