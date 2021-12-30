//
//  main.cpp
//  Task3_PRJKT
//
//  Created by Ivan on 01.04.2021.
//

#include <iostream>
#include <cmath>
using namespace std;
#define SIZE 16



class Exeption
{
    private:
    char *str;
    
    public:
    Exeption(int ERR_CODE);
    const char* GetName() const {return str;}
     
    ~Exeption();
};

Exeption::Exeption(int ERR_CODE)
{
    {
        if (ERR_CODE == 1)
        {
            size_t SIZE_T = strlen("Error when creating rectangle\n") + 1;
            this->str = new char[SIZE_T];

            snprintf(str, SIZE_T, "Error when creating rectangle\n");
            return ;
        }
        if (ERR_CODE == 2)
        {
            size_t SIZE_T = strlen("Error when creating Circle\n") + 1;
            this->str = new char[SIZE_T];

            
            snprintf(str, SIZE_T, "Error when creating Circle\n");
            return ;
        }
        if (ERR_CODE == 3)
        {
            size_t SIZE_T = strlen("Error when creating Triangle\n") + 1;
            this->str = new char[SIZE_T];

            
            snprintf(str, SIZE_T, "Error when creating Triangle\n");
            return ;
        }
        if (ERR_CODE == 4)
        {
            size_t SIZE_T = strlen("Error when creating Pyramid\n") + 1;
            this->str = new char[SIZE_T];

            
            snprintf(str, SIZE_T, "Error when creating Pyramid\n");
            return ;
        }
        if (ERR_CODE == 5)
        {
            size_t SIZE_T = strlen("Error when creating Cilinder\n") + 1;
            this->str = new char[SIZE_T];

            
            snprintf(str, SIZE_T, "Error when creating Cilinder\n");
            return ;
        }
        if (ERR_CODE == 6)
        {
            size_t SIZE_T = strlen("Error when creating Conus\n") + 1;
            this->str = new char[SIZE_T];

            
            snprintf(str, SIZE_T, "Error when creating Conus\n");
            return ;
        }
        
        
        
        else
        {
            char* str = new char[strlen("ERROR\n") + 1];
            strcpy (str, "ERROR\n");
            return;
        }
        
        
        
    }
 }
Exeption::~Exeption()
{
    delete [] str;
}














class Figure {
protected:
    //double a;
public:

    virtual double Volume() = 0;
    virtual double Square() = 0;
};

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
double Rectangle::Volume()
{
    return 0;
}
double Rectangle::Square()
{
    return a*b;
}



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
double Circle::Volume()
{
    return 0;
}
double Circle::Square()
{
    return 3.14*a*a;
}



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
double Triangle::Volume()
{
    return 0;
}
double Triangle::Square()
{
    double p = (a + b + c)/2;
    
    return sqrt(p*(p-a)*(p-b)*(p-c));
}





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
double Cilinder::Volume()
{
    return Circle::Square()*Rectangle::a;
}
double Cilinder::Square()
{
    return Circle::Square() + Rectangle::Square();
    
}



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
double Conus::Volume()
{
    return (Triangle::a * Circle::Square())/3;
}
double Conus::Square()
{
    return 3.14 * Circle::a * sqrt(pow(Circle::a, 2) + pow(Triangle::a, 2)) + Circle::Square();
}






int main() {
    try{
        
        
        
        Figure *pa;
        Rectangle F(3,2);
        pa = &F;
        pa->Square();
    /*
        Rectangle F(3,2);
        cout << F.Square() << endl;
        cout << F.Volume() << endl;
    */
    /*
        Circle F(3);
        cout << F.Square() << endl;
        cout << F.Volume() << endl;
    */
    /*
        Triangle F(3, 4, 5);
        cout << F.Square() << endl;
        cout << F.Volume() << endl;
    */
    /*
        Pyramid F(6, -5);
        cout << F.Square() << endl;
        cout << F.Volume() << endl;
    */
    /*
        Cilinder F(6, 5);
        cout << F.Square() << endl;
        cout << F.Volume() << endl;
    */
    /*
        Conus F(6, -5);
        cout << F.Square() << endl;
        cout << F.Volume() << endl;
    */
        
        
    }
    catch(const Exeption &ERROR)
    {
        cout << ERROR.GetName();
    }
    catch(bad_alloc)
    {
        cout << "ALLOC ERROR\n";
    }
    catch(...)
    {
        cout << "ERROR\n";
    }
    
    
    
    return 0;
}
