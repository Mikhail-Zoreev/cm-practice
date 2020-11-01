#include "spline.h"

Spline::Spline()
{

}

Spline::~Spline()
{

}

void Spline::insert(const QPointF& point)
{
    auto iterator = m_points.begin();
    while (iterator != m_points.end() && iterator->x() < point.x())
    {
        iterator++;
    }
    m_points.insert(iterator, point);
    if (m_points.size() > 2)
    {
        update();
    }
}

const std::vector<QPointF>& Spline::points() const
{
    return m_points;
}

const std::vector<double> Spline::a() const
{
    return m_a;
}

const std::vector<double> Spline::b() const
{
    return m_b;
}

const std::vector<double> Spline::c() const
{
    return m_c;
}

const std::vector<double> Spline::d() const
{
    return m_d;
}

void Spline::update()
{
    m_a = std::vector<double>(m_points.size());
    m_b = std::vector<double>(m_points.size());
    m_c = std::vector<double>(m_points.size());
    m_d = std::vector<double>(m_points.size());
    std::vector<double> h(m_points.size());

    for (size_t i = 1; i < h.size(); i++)
    {
        h[i] = m_points[i].x() - m_points[i - 1].x();
    }

    m_c[0] = m_c[m_c.size() - 1] = 0;
    tridiagonalMatrixAlgorithm();

    for (size_t i = 1; i < m_points.size(); i++)
    {
        m_a[i] = m_points[i].y();
        m_d[i] = (m_c[i] - m_c[i - 1]) / (3 * h[i]);
        m_b[i] = (m_a[i] - m_a[i - 1]) / h[i] + ((2 * m_c[i] + m_c[i - 1]) / 3) * h[i];
    }
}

void Spline::tridiagonalMatrixAlgorithm()
{

}
