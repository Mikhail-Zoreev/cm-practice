#include "seidelmethodsolver.h"

Column SeidelMethodSolver::solve(const Matrix &A, const Column &b, const Column &x, double epsilon)
{
    if (A.zeroOnDiagonal())
    {
        throw std::runtime_error("Matrix has zeron on diagonal");
    }
    if (!A.diagonalPredominant())
    {
        throw std::runtime_error("Matrix is not diagonal-predominant");
    }
    Column x_current = x;
    Column x_previous;
    do
    {
        x_previous = x_current;
        for (size_t i = 0; i < A.size(); i++)
        {
            double temp = 0;
            for (size_t j = 0; j < i; j++)
            {
                temp += A(j, i) * x_current[j];
            }
            for (size_t j = i + 1; j < A.size(); j++)
            {
                temp += A(j ,i) * x_previous[j];
            }
            x_current[i] = (b[i] - temp) / A(i, i);
        }
    }
    while (!Matrix::converge(x_current, x_previous, epsilon));
    return x_current;
}
