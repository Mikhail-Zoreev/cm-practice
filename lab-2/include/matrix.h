#pragma once

#include <vector>
#include <stdexcept>

using Row = std::vector<double>;
using Column = std::vector<double>;

class Matrix
{
protected:
    size_t m_size;
    std::vector<double> m_vector;

public:
    Matrix() = delete;
    Matrix(size_t size = 0);
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix);
    ~Matrix();

    Column operator*(const Column& column);

    Matrix& operator=(const Matrix& matrix);
    Matrix& operator=(Matrix&& matrix);

    double operator()(size_t column, size_t row) const;
    const double& operator()(size_t column, size_t row);
};
