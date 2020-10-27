#pragma once

#include <stdexcept>
#include <vector>

#include <QPointF>

class Spline
{
protected:
    std::vector<QPointF> m_points;

    std::vector<double> m_a;
    std::vector<double> m_b;
    std::vector<double> m_c;
    std::vector<double> m_d;

public:
    Spline();
    ~Spline();

    void insert(const QPointF& point);

    QPointF point(size_t index);
    double a(size_t index);
    double b(size_t index);
    double c(size_t index);
    double d(size_t index);

protected:
    void update();

private:
    void tridiagonalMatrixAlgorithm();
};
