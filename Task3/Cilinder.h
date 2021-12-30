#ifndef Cil
#define Cil
#include "Figure.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Exeption.h"



class Cilinder: public Circle, public Rectangle
{
public:
    Cilinder(double R = 1, double H = 1): Circle(R), Rectangle(H, 3.14*2*R)
    {
        if (R < 0 || H < 0 )
            throw Exeption(5);
    }
    double Volume();
    double Square();
};


#endif


