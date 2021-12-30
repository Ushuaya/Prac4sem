#include "Cilinder.h"
#include <iostream>

double Cilinder::Volume()
{
    return Circle::Square()*Rectangle::a;
}
double Cilinder::Square()
{
    return Circle::Square() + Rectangle::Square();
    
}
