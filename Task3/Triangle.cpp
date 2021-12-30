#include "Triangle.h"
#include <iostream>

double Triangle::Volume()
{
    return 0;
}
double Triangle::Square()
{
    double p = (a + b + c)/2;
    
    return sqrt(p*(p-a)*(p-b)*(p-c));
}
