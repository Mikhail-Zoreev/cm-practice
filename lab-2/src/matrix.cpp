#include "matrix.h"

Matrix::Matrix(size_t size) : m_size(size), m_vector(size * size)
{

}

Matrix::Matrix(const Matrix& matrix) : m_size(matrix.m_size), m_vector(matrix.m_vector)
{

}

Matrix::Matrix(Matrix&& matrix) : m_size(matrix.m_size), m_vector(std::move(matrix.m_vector))
{

}

Matrix::~Matrix()
{
    m_size = 0;
    m_vector.clear();
}


Column Matrix::operator*(const Column& column)
{
    if (m_size != column.size())
    {
        throw std::runtime_error("Wrong size");
    }
    Column result(m_size);
    for (size_t i = 0; i < m_size; i++)
    {
        double sum = 0;
        for (size_t j = 0; j < m_size; j++)
        {
            sum += (*this)(i, j) * column[j];
        }
        result[i] = sum;
    }
    return result;
}

Matrix& Matrix::operator=(const Matrix& matrix)
{
    m_size = matrix.m_size;
    m_vector = matrix.m_vector;
    return *this;
}

Matrix& Matrix::operator=(Matrix&& matrix)
{
    m_size = matrix.m_size;
    m_vector = std::move(matrix.m_vector);
    return *this;
}

double Matrix::operator()(size_t column, size_t row) const
{
    return m_vector[m_size * row + column];
}

double &Matrix::operator ()(size_t column, size_t row)
{
    return m_vector[m_size * row + column];
}
