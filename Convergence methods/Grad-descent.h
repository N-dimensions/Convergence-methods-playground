#include "Matrixfun.h"
using namespace std;
float f(mat w, mat x, mat y)
{
    float func;
    mat op = w * x - y;
    func = sum(sqr(op)) / x.col;
    return func;
}
mat grad(mat w, mat x, mat y)
{
    int i, j;
    //cout << "reporting sir " << endl;
    mat opi = (w * x - y) * T(x);             //w is a row vec, x is a column vec, y is a row vec
    //cout << "The gradient: " << endl;
    mat opf(w.row, w.col);
    for (i = 0; i < w.col; i++)
    {
        opf.m[0][i] = 0;
        for (j = 0; j < opi.row; j++)
        {
            opf.m[0][i] = opf.m[0][i] + opi.m[j][i];
        }
        opf.m[0][i] = 2 * opf.m[0][i] / x.col;
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
