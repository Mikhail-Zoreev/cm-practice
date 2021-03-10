#include "ludecompositionmethodsolver.h"

Column LUDecompositionMethodSolver::solve(const Matrix &A, const Column &b, const Column&, double)
{
    if (A(0, 0) == 0)
    {
        throw std::runtime_error("Matrix A[0][0] equals to zero");
    }
    size_t size = A.size();
    Matrix L(size), U(size);
    for (size_t i = 0; i < size; i++)
    {
        U(i, 0) = A(i, 0);
        L(0, i) = A(0, i) / U(0, 0);
    }

    for (size_t i = 1; i < size; i++)
    {
        for (size_t j = i; j < size; j++)
        {
            double sum = 0.0;
            for (size_t k = 0; k < i; k++)
            {
                sum += L(k, i) * U(j ,k);
            }
            U(j, i) = A(j, i) - sum;
        }
        for (size_t j = i; j < size; j++)
        {
            double sum = 0.0;
            for (size_t k = 0; k < i; k++)
            {
                sum += L(k, j) * U(i, k);
            }
            L(i, j) = (A(i, j) - sum) / U(i, i);
        }
    }

    Column y(size);
    for (size_t i = 0; i < size; i++)
    {
        double sum = 0.0;
        for (size_t j = 0; j < i; j++)
        {
            sum += L(j, i) * y[j];
        }
        y[i] = b[i] - sum;
    }

    Column result(size);
    for (int64_t i = size - 1; i >= 0; i--)
    {
        double sum = 0.0;
        for (size_t j = i + 1; j < size; j++)
        {
            sum += U(j, i) * result[j];
        }
        result[i] = (y[i] - sum) / U(i, i);
    }

    return result;
}

std::string LUDecompositionMethodSolver::name() const
{
    return "LU decomposition";
}
