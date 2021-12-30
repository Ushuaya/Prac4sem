#ifndef CUBE_H
#define CUBE_H
#include "Figure.h"
#include "Exeption.h"


class Circle: virtual public Figure {
protected:
    double a;
public:
    Circle (double x = 1)
    {
        if (x < 0)
            throw Exeption(2);
        a = x;
    }
    double Volume();
    double Square();
};

#endif 
