#pragma once

#include <array>
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

    bool available() const;

    void clear();

    void insert(const QPointF& point);

    const std::vector<QPointF>& points() const;

    double value(size_t i, double x) const;

protected:
    void update();

private:
    void tridiagonalMatrixAlgorithm();
};
