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

    const std::vector<QPointF>& points() const;
    const std::vector<double> a() const;
    const std::vector<double> b() const;
    const std::vector<double> c() const;
    const std::vector<double> d() const;

protected:
    void update();

private:
    void tridiagonalMatrixAlgorithm();
};
