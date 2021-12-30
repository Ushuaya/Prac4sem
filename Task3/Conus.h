#ifndef Con
#define Con
#include "Circle.h"
#include "Triangle.h"



class Conus: public Circle, public Triangle
{
public:
    Conus(double R = 1, double H = 1): Circle(R), Triangle(H, H, H)
    {
        if (R < 0 || H < 0 )
            throw Exeption(6);
    }
    double Volume();
    double Square();
};





#endif

