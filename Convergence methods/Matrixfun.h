#include <iostream>
class mat
{
public:
    int row = 0;
    int col = 0;
    float** m;
    mat(int r, int c)
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
    ~mat()
    {
        for (int i = 0; i < row; i++)
        {
            delete[] m[i];
        }
        delete[] m;
        //std::cout << "Memory deleted..." << std::endl;
    }
    mat operator =(mat M1)
    {
        int i, j;
        mat temp(M1.row, M1.col);
        for (i = 0; i < M1.row; i++)
        {
            for (j = 0; j < M1.col; j++)
            {
                temp.m[i][j] = M1.m[i][j];
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
mat T(mat* M1)
{
    mat M2(M1->col, M1->row);
    int i, j;
    for (i = 0; i < M1->col; i++)
    {
        for (j = 0; j < M1->row; j++)
        {
            M2.m[i][j] = M1->m[j][i];
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
            M1.m[i][j] = M1.m[i][j] * M1.m[i][j];
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
            M1.m[i][j] = a * M1.m[i][j];
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
    int i, j;
    float sum = 0;
    for (i = 0; i < M1.row; i++)
    {
        for (j = 0; j < M1.col; j++)
        {
            sum = sum + M1.m[i][j];
        }
    }
    return sum;
}
