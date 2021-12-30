#include "Exeption.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>


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
