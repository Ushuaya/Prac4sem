#include "Pyramid.h"
#include <iostream>


double Pyramid::Volume()
{
    if (Rectangle::a == Rectangle::b && Triangle::a == Rectangle::a && Triangle::b == Triangle::c)
        return sqrt(pow(Triangle::b,2)- (pow(Triangle::a,2)/2)) * (pow(Rectangle::a,2))/3;
    else
        throw 4;
}
double Pyramid::Square()
{
    return Rectangle::Square() + 4 * Triangle::Square();
    
}
