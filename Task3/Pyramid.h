#ifndef Pyr
#define Pyr
#include "Figure.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Exeption.h"


class Pyramid: public Rectangle, public Triangle
{
public:
    Pyramid(double x1 = 1, double x2 = 1): Rectangle(x1, x1), Triangle(x1, x2, x2)
    {
        if (x2 < 0 || x1 < 0 )
            throw Exeption(4);
    }
    double Volume();
    double Square();
};





#endif

