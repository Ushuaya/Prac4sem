//
//  main.cpp
//  Task2
//
//  Created by Ivan on 10.03.2021.
//
#include "matrix.h"

matrix::matrix(const matrix& matr){

    matx_m = matr.matx_m;
    matx_n = matr.matx_n;
    mtrx = new double*[matx_n];
    //matx_n = n;
    //matx_m = m;
    for (int i = 0; i < matx_n; i++)
    {
        mtrx[i] = new double[matx_m];
        for(int j = 0; j < matx_m; j++)
        {
            mtrx[i][j] = matr.mtrx[i][j];
        }
    }
    //mas = new double [matx_n*m];
    /*
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            mas[i*n+j]=matr.mas[i*n+j];
*/
}

matrix::~matrix()
{
    cout << "DESTRUCTOR\n";
    for (int i = 0; i < matx_n; i++)
        delete[] mtrx[i];

    delete[] mtrx;
}


matrix matrix::operator[](int num) const
{
    if (num >= 1 && num <= matx_n)
    {
        matrix buf(1, matx_m);

        for (int j = 0; j < matx_m; j++)
        {
            buf.mtrx[0][j] =  mtrx[num-1][j];
        }

        return buf;
    }

    if (num >= 1 && num <= matx_m)
    {
        matrix buf(matx_n, 1);
        
        for (int i = 0; i < matx_n; i++)
        {
            buf.mtrx[i][0] = mtrx[i][num-1];
        }

        return buf;
    }

    throw ("There is no such string or column");
}


matrix operator/(matrix &M_F_1, matrix &M_F_2){
    if(M_F_1.matx_m == M_F_2.matx_m){
        matrix buf(M_F_1.matx_n + M_F_2.matx_n, M_F_1.matx_m);
        for(int i = 0; i < M_F_1.matx_n; i++)
            for(int j = 0; j < M_F_1.matx_m; j++){
                buf.mtrx[i][j] = M_F_1.mtrx[i][j];
            }
        for(int i = 0; i < M_F_2.matx_n; i++)
            for(int j = 0; j < M_F_1.matx_m; j++)
                buf.mtrx[i + M_F_1.matx_n][j] = M_F_2.mtrx[i][j];
        return buf;
    }
    else{
        throw "Not suitable matrix for/";
    }
}


matrix operator|(matrix &M_F_1, matrix &M_F_2){
        matrix buf(M_F_1.matx_m, M_F_1.matx_n + M_F_2.matx_n);
        if(M_F_1.matx_n == M_F_2.matx_n){
            matrix buf(M_F_1.matx_n, M_F_1.matx_m + M_F_2.matx_m);
            for(int i = 0; i < M_F_1.matx_n; i++)
                for(int j = 0; j < M_F_1.matx_m; j++){
                    buf.mtrx[i][j] = M_F_1.mtrx[i][j];
                }
            for(int i = 0; i < M_F_1.matx_n; i++)
                for(int j = 0; j < M_F_2.matx_m; j++)
                    buf.mtrx[i][j + M_F_1.matx_m] = M_F_2.mtrx[i][j];
            return buf;
        }
        else{
            throw"Not suitable matrix for|";
        }
}

bool operator == (matrix &M_F_1, matrix &M_F_2){
    if(M_F_1.matx_m == M_F_2.matx_m && M_F_1.matx_n == M_F_2.matx_n)
    {
        for(int i = 0; i < M_F_1.matx_n; i++)
            for(int j = 0; j < M_F_1.matx_m; j++)
                if(M_F_1.mtrx[i][j] != M_F_2.mtrx[i][j])
                    return false;
        return true;
    }
    else
        return false;
}
bool operator != (matrix &M_F_1, matrix &M_F_2){
    if(M_F_1.matx_m == M_F_2.matx_m && M_F_1.matx_n == M_F_2.matx_n)
    {
        for(int i = 0; i < M_F_1.matx_n; i++)
            for(int j = 0; j < M_F_1.matx_m; j++)
                if(M_F_1.mtrx[i][j] != M_F_2.mtrx[i][j])
                    return true;
        return false;
    }
    else
        return true;
}

matrix operator*(matrix &M_F_1, matrix &M_F_2){
        if(M_F_1.matx_m == M_F_2.matx_n){
            matrix buf(M_F_1.matx_n, M_F_2.matx_m);
            int i,j,k;
            for(i = 0; i < M_F_1.matx_n; i++)
                for(j = 0; j < M_F_2.matx_m; j++){
                    buf.mtrx[i][j]=0;
                    for(k = 0; k < M_F_1.matx_m; k++)
                        buf.mtrx[i][j] = buf.mtrx[i][j] + (M_F_1.mtrx[i][k] * M_F_2.mtrx[k][j]);
                }
            return buf;
        }
        else{
            throw"Not suitable matrix for*";
        }
}
matrix matrix::operator -() const
{
    matrix buf(matx_n, matx_m);
    for(int i = 0; i < matx_n; i++)
        for(int j = 0; j < matx_m; j++)
        {
            buf.mtrx[i][j] = -mtrx[i][j];
        }
    return buf;
}

matrix operator +(matrix &M_F_1, matrix &M_F_2){
    
    if(M_F_1.matx_m == M_F_2.matx_m && M_F_1.matx_n == M_F_2.matx_n){
            
                matrix buf(M_F_1.matx_n, M_F_1.matx_m);
                for(int i = 0; i < M_F_1.matx_n; i++)
                    for(int j = 0; j < M_F_1.matx_m; j++)
                        buf.mtrx[i][j]=M_F_1.mtrx[i][j] + M_F_2.mtrx[i][j];
            //    cout<<buf<<endl;
                return buf;
            }
            else{
                throw"Not suitable matrix for +";
}
}

matrix operator -(matrix &M_F_1, matrix &M_F_2){
    
    if(M_F_1.matx_m == M_F_2.matx_m && M_F_1.matx_n == M_F_2.matx_n){
            
                matrix buf(M_F_1.matx_n, M_F_1.matx_m);
                for(int i = 0; i < M_F_1.matx_n; i++)
                    for(int j = 0; j < M_F_1.matx_m; j++)
                        buf.mtrx[i][j]=M_F_1.mtrx[i][j] - M_F_2.mtrx[i][j];
            //    cout<<buf<<endl;
                return buf;
            }
            else{
                throw"Not suitable matrix for +";
}
}




//11)


//5)
matrix::matrix( char* string_f)
{
    //cout << string_f << endl;
    int stack = 0;
    int matx_n_f = 0;
    int matx_m_f = 0;//quantity of columns
    int all_matr = 0;//quantity of numbers
    bool check = true;
    stack = 0;
    check = true;
    
    
    //SEQUENCE VALIDATION AND SEARCING FOR COLUMN AND ALL_NUMBER VALUE
    for(int i = 0; i < strlen(string_f); i++)
    {
        switch (string_f[i]){
            case '{':
                stack ++;
            break;
                    
            case '}':
                check = false;
                //cout << "DD";
                stack --;
                //i = strlen(string_f);
            break;
                    
            case ',':
                
            break;
                
            case ' ':
                
            break;
                

                
        default:
            if (string_f[i] >= '0' && string_f[i] <= '9')
            {
                if (check)
                    matx_m_f++;
                all_matr++;
                while ((string_f[i] >= '0' && string_f[i] <= '9') || string_f[i] == '.')
                {
                    i++;
                }
                i--;
            }
            else{
                cout << "WRONG_INPUT_1\n";
                i = strlen(string_f);
                matx_n_f = 0;
                matx_m_f = 0;
                stack = -1;
            }
        }
    }
    // Now we know matx_m_f and all_matr values

    
    //DEBUG
    //cout << "STRINGS:" << matx_m_f << endl;
    //cout << "ALL:" << all_matr << endl;
    
    stack = 0;
    if (stack == 0)//if there are "}" symbol => correct  sequence
    {
        stack = 0;
        
        //searching for quantity of STRINGS
        if ((all_matr % matx_m_f) == 0)
        {
            matx_n_f = all_matr/matx_m_f;
        }
        else
        {
            matx_n_f = all_matr/matx_m_f;
            matx_n_f ++;
        }
        
        //DEBUG
        //cout << "COLUMNS:" << matx_n_f << endl;
        
        //Buf to save all numbers
        double* M_BUF = new double [matx_n_f*matx_m_f];
        for(int i = 0; i < matx_n_f*matx_m_f; i++)
        {
            M_BUF[i] = 0;
        }
        // SPLITTING OF THE STRING IN ORDER TO EJECT NUMBERS TO SAVE THEM INTO THE BUF
        char sep[]= "/ ,}{";
        char *istr;
        char *string_f_tmp = new char[((int)strlen(string_f))];
        strcpy(string_f_tmp, string_f);
        istr = strtok (string_f_tmp ,sep);//ejection of a num
        double Num=0;
        Num = atof (istr);
        M_BUF[0] = Num;
        for(int i = 1; i < all_matr; i++)
        {

            istr = strtok (NULL ,sep);//ejection of a num
            double Num=0;
            Num = atof (istr);
            M_BUF[i] = Num;
            
        }
        
        //DEBUG
        /*
        for(int i = 0; i < matx_n_f*matx_m_f; i++)
        {
            cout <<  M_BUF[i] << " | ";
        }
         */
        
        //NOW WE CREATE MATRIX
        //WITH EXISTING VALUES AND SIZES
        matrix M_F (matx_n_f,matx_m_f);
        matx_n = matx_n_f;
        matx_m = matx_m_f;
        
        mtrx = new double*[matx_n];
        for (int i = 0; i < matx_n; i++)
        {
            mtrx[i] = new double[matx_m];
            for(int j = 0; j < matx_m; j++)
            {
                mtrx[i][j] = M_BUF[i*matx_m + j];
            }
        }
        cout << endl;
        //cout << M_F;
        //delete [] M_BUF;
        //delete [] string_f_tmp;
        
        
        
    }
    else
    {
        cout << "WRONG_INPUT_2\n";
        //i = strlen(string_f);
        matx_n_f = 0;
        matx_m_f = 0;
    }
    
    
}


//7)
matrix matrix::diagonal( double* vals, int n )
{
    matrix M_F (n,n);
    for (int i = 0; i < n; i++)
    {
        M_F.set(i, i, vals[i]);
    }
    //cout << M_F;
    return M_F;
}

//1)
matrix::matrix( int n, int m)
{
    mtrx = new double*[n];
    matx_n = n;
    matx_m = m;
    for (int i = 0; i < n; i++)
    {
        mtrx[i] = new double[m];
        for(int j = 0; j < m; j++)
        {
            mtrx[i][j] = 0;
        }
    }
    
}

//3)
matrix::matrix( double*str, int m )
{
    matx_m = m;
    matx_n = 1;
    mtrx = new double*[matx_n];
    mtrx[0] = new double[matx_m];
    for (int i = 0; i < m; i++)
    {
        mtrx[0][i] = str[i];
    }
}

//4)
matrix::matrix(int n , double*colmn)
{
    mtrx = new double*[n];
    matx_m = 1;
    matx_n = n;
    //mtrx[0] = new double[n];
    for (int i = 0; i < n; i++)
    {
        mtrx[i] = new double[matx_m];
        mtrx[i][0] = colmn[i];
    }
}
/*
matrix::matrix(int n , double*colmn)
{
    matx_n = n;
    matx_m = 1;
    mtrx = new double *[matx_n];
    for(int j = 0; j < matx_n; j++)
    {
        mtrx[j] = new double;
        mtrx[j][0] = colmn[j];
    }
}
 */

//14)
ostream& operator<<(ostream &out,matrix x){
    for(int i=0; i < x.matx_n; i++){
        for(int j=0; j < x.matx_m; j++)
            out << x.mtrx[i][j] << " ";
        out << endl;
    }
    //out << x.matx_m << " " << x.matx_n;
return out;
}

//13)
matrix operator *(matrix &M_F, int scalar_f){
    for(int i=0; i < M_F.matx_n; i++){
        for(int j=0; j < M_F.matx_m; j++)
            M_F.mtrx[i][j] *= scalar_f;
    }
    //out << x.matx_m << " " << x.matx_n;
    return M_F;
}

//6)
matrix matrix::identity( int n )
{
    //cout << "HELLO\n";
    matrix M_F (n, n);
    for (int i = 0; i < n; i++)
    {
        M_F.set(i, i, 1);
    }
    //cout << M_F;
    return M_F;
}

//10)
void matrix::set(int a, int b, double c)
{
    mtrx[a][b] = c;
}

//2)
matrix::matrix(double a)
{
    matx_n = 1;
    matx_m = 1;
    mtrx = new double *[matx_n];
    mtrx[0] = new double [matx_m];
    mtrx[0][0] = a;
        

}

//8)
int matrix::rows()
{
    //printf("Number of strings: ");
    return matx_n;
}

//9)
int matrix::columns()
{
    //printf("Number of columns: ");
    return matx_m;
}
/*
matrix::~matrix()
{
    cout << "DESTRUCTOR\n";
    for (int i = 0; i < matx_n; i++)
        delete[] mtrx[i];

    delete[] mtrx;
}
*/

