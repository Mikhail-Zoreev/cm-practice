#include "gaussmethodsolver.h"

Column GaussMethodSolver::solve(const Matrix& A, const Column& b, double epsilon)
{
    Matrix A_copy = A;
    Column b_copy = b;
    int i, j, k, size = static_cast<int>(b_copy.size());
    for (j = 0; j < size; j++)
    {
        double alfa = 0;
        //TODO: Line swap
        for (i = j + 1; i < size; i++)
        {
            alfa = A_copy(i, j) / A_copy(j, j);
            for (k = j; k < size; k++)
            {
                A_copy(i, k) -= alfa * A_copy(j, k);
            }
            b_copy[i] -= b_copy[j] * alfa;
        }
    }
    Column result(size);
    result[size - 1] = b_copy[size - 1] / A_copy(size - 1, size - 1);
    for (i = size - 2; i >= 0; i--)
    {
        double sum = 0;
        for (j = i + 1; j < size; j++)
        {
            sum += A_copy(i, j) * result[j];
        }
        result[i] = (b_copy[i] - sum) / A_copy(i, i);
    }
    return result;
}
