// Convergence methods.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
class mat
{
public:
    int row = 0;
    int col = 0;
    float** m;
    mat(int r, int c);
    mat operator =(mat n)
    {
        int i, j;
        mat temp(n.row, n.col);
        for (i = 0; i < n.row; i++)
        {
            for (j = 0; j < n.col; j++)
            {
                temp.m[i][j] = n.m[i][j];
                //cout << n.m[i][j] << "->" << temp.m[i][j] << endl;
            }
        }
        return temp;
    }
    mat operator *(mat M2)
    {
        int i, j, k;
        mat M3(row, M2.col);
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < M2.col; j++)
            {
                M3.m[i][j] = 0;
                for (k = 0; k < col; k++)
                {

                    M3.m[i][j] = M3.m[i][j] + (m[i][k]) * (M2.m[k][j]);
                }
            }

        }
        //cout << "Executed!"<<endl;
        return M3;
    }
    mat operator +(mat M2)
    {
        int i, j;
        mat M3(row, col);
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < col; j++)
            {
                M3.m[i][j] = m[i][j] + M2.m[i][j];
            }
        }
        return M3;
    }
    mat operator -(mat M2)
    {
        int i, j;
        mat M3(row, col);
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < col; j++)
            {
                M3.m[i][j] = m[i][j] - M2.m[i][j];
            }
        }
        return M3;
    }
};
mat::mat(int r, int c)
{
    int i;
    row = r;
    col = c;
    m = new float* [row];
    for (i = 0; i < row; i++)
    {
        m[i] = new float[col];
    }
}
mat T(mat M1)
{
    mat M2(M1.col, M1.row);
    int i, j;
    for (i = 0; i < M1.col; i++)
    {
        for (j = 0; j < M1.row; j++)
        {
            M2.m[i][j] = M1.m[j][i];
        }
    }
    return M2;
}
mat sqr(mat M1)
{
    int i, j;
    for (i = 0; i < M1.row; i++)
    {
        for (j = 0; j < M1.col; j++)
        {
            M1.m[i][j] = M1.m[i][j]* M1.m[i][j];
        }
    }
    return M1;
}
mat mult(float a, mat M1)
{
    int i, j;
    for (i = 0; i < M1.row; i++)
    {
        for (j = 0; j < M1.col; j++)
        {
            M1.m[i][j] = a*M1.m[i][j];
        }
    }
    return M1;
}
int sub(mat* a, mat b)
{
    int i, j;
    for (i = 0; i < a->row; i++)
    {
        for (j = 0; j < a->col; j++)
        {
            a->m[i][j] = a->m[i][j] - b.m[i][j];
        }
    }
    return 0;
}
float sum(mat M1)
{
    int i,j;
    float sum=0;
    for (i = 0; i < M1.row; i++)
    {
        for (j = 0; j < M1.col; j++)
        {
            sum = sum + M1.m[i][j];
        }
    }
    return sum;
}
float f(mat w, mat x, mat y)
{
    float func;
    mat op = w * x - y;
    func = sum(sqr(op))/x.col;
    return func;
}
mat grad(mat w, mat x, mat y)
{
    int i, j;
    //cout << "reporting sir " << endl;
    mat opi = (w * x - y)*T(x);             //w is a row vec, x is a column vec, y is a row vec
    //cout << "The gradient: " << endl;
    mat opf(w.row, w.col);
    for (i = 0; i < w.col; i++)
    {
        opf.m[0][i] = 0;
        for (j = 0; j < opi.row; j++)
        {
            opf.m[0][i] = opf.m[0][i] + opi.m[j][i];
        }
        opf.m[0][i] = 2*opf.m[0][i] / x.col;
        //cout << opf.m[0][i] << "\t";
    }
   // cout << endl;
    return opf;
}
int graddes(mat* w, mat* x, mat* y, int ite, float stpsz, bool st)
{
    int i, j, itno;
    mat gradw(w->row, w->col);
    if (st)
    {
        for (i = 0; i < w->row; i++)
        {
            for (j = 0; j < w->col; j++)
            {
                w->m[i][j] = 0;
            }
        }
    }
    for (itno = 1; itno <= ite; itno++)
    {
        sub(w, mult(stpsz, grad(*w, *x, *y)));
        if (itno <= ite)
        {
            cout << "Iteration number " << itno << " results: " << endl;
            cout << "=====================================================" << endl << endl;
            cout << "Cost equals " << f(*w, *x, *y) << endl;
            cout << "New weights: " << endl;
            for (i = 0; i < w->col; i++)
            {
                cout << w->m[0][i] << "\t";
            }
            cout << endl << endl << endl << endl;
        }
    }
    return 0;
}
int main()
{
    mat w(1, 5), x(5, 1000), y(1, 1000);
    int i, j;
    for (i = 0; i < w.col; i++)
    {
       w.m[0][i] = i+1;
    }
    for (j= 0; j < x.col; j++)
    {
        y.m[0][j] = 0;
        cout << "(\t";
        for (i = 0; i < x.row; i++)
        {
            x.m[i][j] = (float)rand()/(10*rand());
            cout << x.m[i][j] << "\t";
            y.m[0][j] = y.m[0][j] + (i+1)*x.m[i][j];
           // cout << x.m[i][j]<<"\t";
        }
        cout << ") -> " << y.m[0][j] << endl;
        //cout << endl;
    }
    graddes(&w, &x, &y, 1000, 0.01, true);
    return 0;
}