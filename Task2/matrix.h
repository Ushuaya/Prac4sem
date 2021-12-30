//
//  main.cpp
//  Task2
//
//  Created by Ivan on 10.03.2021.
//
#ifndef matrix_h
#define matrix_h

#include <iostream>
#include <cstdlib>
#include <stack>
#include <cstring>
using namespace std;


class matrix
{
private:
    int matx_n;
    int matx_m;
    double **mtrx;
public:
    /*
    matrix()//Default matrix is random 5X5
    {
        //cout << "HELLO\n";
        matx_n = 0;
        matx_m = 0;
        mtrx = new double*[matx_n];
        for (int i = 0; i < matx_n; i++)
        {
            mtrx[i] = new double[matx_m];
            for(int j = 0; j < matx_m; j++)
            {
                double a = (rand())%100;
                //mtrx[i][j] =  (1000*a)/1000.0 ;
                mtrx[i][j] =  a ;

            }
        }
        
        
    }
     */
    
    
    
    static matrix identity( int n );
    matrix( int n, int m);
    matrix( double*, int m );
    matrix(int n , double*);
    matrix(double a);
    matrix( char*);
    
    matrix operator -() const;
    matrix operator [](int idx) const;
    
    
    int rows();
    int columns();
    
    friend ostream& operator<<(ostream &out,matrix x);
    friend matrix operator * (matrix &M_F, int scalar_f);
    friend matrix operator + (matrix &M_F_1, matrix &M_F_2);
    friend matrix operator - (matrix &M_F_1, matrix &M_F_2);
    friend matrix operator * (matrix &M_F_1, matrix &M_F_2);
    friend bool operator == (matrix &M_F_1, matrix &M_F_2);
    friend bool operator != (matrix &M_F_1, matrix &M_F_2);
    friend matrix operator | (matrix &M_F_1, matrix &M_F_2);
    friend matrix operator / (matrix &M_F_1, matrix &M_F_2);

    //friend istream& operator>>(istream &in,matrix x);
    //static matrix identity( int n );
    static matrix diagonal( double* vals, int n );
    void set( int a, int b, double c);
   // matrix matrix[i];
    ~matrix();
    matrix(const matrix& matr);
    
};
#endif
