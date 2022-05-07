// Convergence methods.cpp : This file contains the 'main' function. Program execution begins and ends there.
//#include "Grad-descent.h"
#include "BFGS.h"
using namespace std;
int main()
{
    mat w(1, 5), x(5, 1000), y(1, 1000);
    int i, j;
    for (j= 0; j < x.col; j++)
    {
        y.m[0][j] = 0;
        cout << "(\t";
        for (i = 0; i < x.row; i++)
        {
            x.m[i][j] = (float)rand()/(10*rand());
            cout << x.m[i][j] << "\t";
            y.m[0][j] = y.m[0][j] + ((i+1)*(i+1))*x.m[i][j]+rand()/(10*rand());
           // cout << x.m[i][j]<<"\t";
        }
        cout << ") -> " << y.m[0][j] << endl;
        //cout << endl;
    }
    graddes(&w, &x, &y, 1000, 0.05, true);
    //BFGSd(&w, &x, &y, 2, true);
    return 0;
}