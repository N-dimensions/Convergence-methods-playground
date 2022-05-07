#include "Grad-descent.h"
using namespace std;
float fi(mat w, mat x, mat y)
{
    float func;
    mat op = w * x - y;
    func = sum(sqr(op)) / x.col;
    return func;
}
mat gradi(mat w, mat x, mat y)
{
    int i, j;
    //cout << "reporting sir " << endl;
    mat opi = (w * x - y) * T(&x);             //w is a row vec, x is a column vec, y is a row vec
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
    return T(&opf);
}
mat fdirc(mat hessinv, mat grad)
{
    mat op = hessinv * grad;
    for (int i = 0; i < op.row; i++)
    {
        op.m[i][0] = -op.m[i][0];
    }
    return op;
}
float stpszfd(mat* x,mat *y, mat* P, mat* Grad, mat w)
{
    int i, k, p;
    mat w1 = w;
    bool sat = true, c1=false, c2=false;
    float a[3]={0,0.01,0.02};
    mat del = mult(a[2],* P);
    k = 2;
    p = 2;
    while (sat)
    {
        w1 = w - T(&del);
        c1 = f(w1, *x, *y) <= f(w, *x, *y) + 0.0001 * a[k] * (T(P) * *Grad).m[0][0];
        c2 = (* P * gradi(w1, *x, *y)).m[0][0]>=0.9* a[k] * (T(P) * *Grad).m[0][0];
        if (c1)
        {
            if (c2)
            {
                sat = false;
                continue;
            }
            else
            {
                p = p + 1;
                k = p%3;
                a[k] = a[k] + (a[k] - a[(p - 1) % 3]);
            }
        }
        if (c2)
        {
            if (!c1)
            {
                p = p + 1;
                k = p % 3;
                a[k] = (a[k] + a[(p - 1) % 3])/2;
            }
        }
    }
    return a[k];
}
int BFGSd(mat* w, mat* x, mat* y, int ite, bool st)
{
    mat Binv(w->col, w->col);
    mat X = T(x);
    mat Y = T(y);
    mat W = T(w);
    mat Grad = T(w);
    int i, j, k;
    mat P(w->col, w->row);
    //setting Hessian inv to be identity
    for (i = 0; i < Binv.row; i++)
    {
        for (j = 0; j < Binv.col; j++)
        {
            if (i == j)
            {
                Binv.m[i][j] = 1;
            }
        }
    }
    for (k = 0; k < ite; k++)
    {
        Grad = gradi(*w, *x, *y);
        //Finding direction
        P = fdirc(Binv, Grad);
        //Finding stepsize
        cout<<stpszfd(x, y, &P, &Grad, *w);
    }
    return 0;
}
