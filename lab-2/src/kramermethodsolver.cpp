#include "kramermethodsolver.h"

Column KramerMethodSolver::solve(const Matrix &A, const Column &b, double epsilon)
{
    size_t size = b.size();
    Column temp, result;
    double determinant = A.determinant();
    if (determinant == 0)
    {
        throw std::runtime_error("Zero determinant");
    }
    for (size_t i = 0; i < size; i++)
    {
        Matrix A_copy = A;
        for (size_t j = 0; j < size; j++)
        {
            A_copy(i, j) = b[j];
        }
        temp.push_back(A_copy.determinant());
    }
    for (auto value : temp)
    {
        result.push_back(value / determinant);
    }
    return result;
}
