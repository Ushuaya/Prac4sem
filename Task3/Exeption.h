#ifndef Exe
#define Exe

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <iostream>
#include <cmath>


class Exeption
{
    private:
    char *str;
    
    public:
    Exeption(int ERR_CODE);
    const char* GetName() const {return str;}
     
    ~Exeption();
};


#endif
