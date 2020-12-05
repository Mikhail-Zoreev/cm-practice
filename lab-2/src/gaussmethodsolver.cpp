#include "gaussmethodsolver.h"

Column GaussMethodSolver::solve(const Matrix& A, const Column& b, const Column&, double)
{
    Matrix A_copy = A;
    Column b_copy = b;
    size_t size = static_cast<int>(b_copy.size());
    for (size_t j = 0; j < size; j++)
    {
        double alfa = 0;
        if (A_copy(j, j) == 0)
        {
            for (size_t k = j + 1; k < A_copy.size(); k += 1)
            {
                if (A_copy(j, k) != 0)
                {
                    for (size_t i = j; i < A_copy.size(); i++)
                    {
                        std::swap(A_copy(i, j), A_copy(i, k));
                    }
                    std::swap(b_copy[j], b_copy[k]);
                    break;
                }
            }
            if (A_copy(j, j) == 0)
            {
                break;
            }
        }
        for (size_t i = j + 1; i < size; i++)
        {
            alfa = A_copy(j, i) / A_copy(j, j);
            for (size_t k = j; k < size; k++)
            {
                A_copy(k, i) -= alfa * A_copy(k, j);
            }
            b_copy[i] -= b_copy[j] * alfa;
        }
    }
    Column result(size);
    result[size - 1] = b_copy[size - 1] / A_copy(size - 1, size - 1);
    for (int64_t i = size - 2; i >= 0; i--)
    {
        double sum = 0;
        for (size_t j = i + 1; j < size; j++)
        {
            sum += A_copy(j, i) * result[j];
        }
        result[i] = (b_copy[i] - sum) / A_copy(i, i);
    }
    return result;
}

std::string GaussMethodSolver::name() const
{
    return "Gauss";
}
