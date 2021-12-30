//
//  main.cpp
//  Task3_PRJKT
//
//  Created by Ivan on 01.04.2021.
//

#include <iostream>
#include <cmath>
#include "Figure.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Pyramid.h"
#include "Conus.h"
#include "Cilinder.h"


#include "Exeption.h"



using namespace std;
#define SIZE 16



int main() {
    try{

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
