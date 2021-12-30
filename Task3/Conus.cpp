#include "Conus.h"
#include <iostream>

double Conus::Volume()
{
    return (Triangle::a * Circle::Square())/3;
}
double Conus::Square()
{
    return 3.14 * Circle::a * sqrt(pow(Circle::a, 2) + pow(Triangle::a, 2)) + Circle::Square();
}
