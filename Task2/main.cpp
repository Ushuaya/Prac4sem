//
//  main.cpp
//  Task2
//
//  Created by Ivan on 10.03.2021.
//
#include "matrix.h"

int main(int argc, const char * argv[]) {
    srand(4541);
    // insert code here...
    //cout << "Hello, World!\n";
    
    try{
    //matrix A = matrix::identity((int)5);
    
    double C[10] = {1,2,3,4,5,6,7,8,9,0};
    //double B[10] = {1,2,3,4,5,6,7,8,9,0, 4, 4, 4};
    char STR_1[] = "{1 0 0} 0 2 3 0 0 1";
    char STR_2[] = "{1 0 0  2} 3 0 0 1  4 4 4 8 ";
        matrix A(STR_1);
        matrix B(STR_2);
        cout << "SECOND MATRIX 4th SRTING IS: \n"<< ((B[4])) << endl;
        cout << "FIRST MATRIX IS: \n" << A << endl;

        cout << "SECOND MATRIX IS: \n"<< B << endl;
        cout << "identity matrix: \n" << matrix::identity((int)5) << endl;
        cout << "diagonal matrix: \n" << matrix::diagonal(C, 5) << endl;
        cout << "QUANTITY OF STRINGS IN FIRST MATRIX IS: \n" << A.rows() << endl;
        cout << "FIRST MATRIX MULTIPLIED BY 5 IS: \n" << A*5 << endl;
        cout << "A+A  =  \n"<< A+A << endl;
        cout << "A-A  =  \n"<< A-A << endl;
        cout << "A*A  =  \n"<< A*A << endl;
        cout << "-A   =  \n"<< (-A) << endl;
        cout << "A==A? = \n"; cout<< (A==A); cout << endl << endl;
        cout << "A!=A? = \n"; cout<< (A!=A); cout << endl << endl;
        cout << "A|A  =  \n"; cout<< (A|A) ; cout << endl << endl;
        cout << "A/A  =  \n"; cout<< (A/A) ; cout << endl << endl;
        
    //matrix A = matrix::diagonal(B, 5);
    //matrix A(10);
    //cout << A.columns();
    //matrix A(10, B);
    //matrix A((double)1);
    //int scalar=5;
    //matrix A(B, 10);
    //cout << A*scalar;
    //A*5;
    //cout << A;
        /*
    matrix A(STR_1); //cout << STR << endl;
    cout << A << endl;

        matrix A(STR_1);
    cout << B << endl;


    cout << ((B[4]));
    
    */
    }
    catch(const char*str)
    {
        cout << str << endl;
    }
    
    return 0;
}


