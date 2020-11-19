#include "spline.h"

Spline::Spline()
{

}

Spline::~Spline()
{

}

bool Spline::aviable() const
{
    return (m_points.size() > 3);
}

void Spline::clear()
{
    m_points.clear();
    m_a.clear();
    m_b.clear();
    m_c.clear();
    m_d.clear();
}

void Spline::insert(const QPointF& point)
{
    auto iterator = m_points.begin();
    while (iterator != m_points.end() && iterator->x() < point.x())
    {
        iterator++;
    }
    m_points.insert(iterator, point);
    if (aviable())
    {
        update();
    }
}

const std::vector<QPointF>& Spline::points() const
{
    return m_points;
}

double Spline::value(size_t i, double x) const
{
    double a = m_a[i], b = m_b[i], c = m_c[i], d = m_d[i];
    double delta = x - m_points[i].x();
    return (a + b * delta + (c / 2.) * delta * delta + (d / 6.) * delta * delta * delta);
}

void Spline::update()
{
    m_a = std::vector<double>(m_points.size());
    m_b = std::vector<double>(m_points.size());
    m_c = std::vector<double>(m_points.size());
    m_d = std::vector<double>(m_points.size());
    std::vector<double> h(m_points.size());
    tridiagonalMatrixAlgorithm();
}

void Spline::tridiagonalMatrixAlgorithm()
{
    size_t n = m_points.size() - 1;
    std::vector<double> h(n);
    for (size_t i = 0; i < n; i++)
    {
        h[i] = m_points[i + 1].x() - m_points[i].x();
    }
    std::vector<double> diagMain(n - 1);
    std::vector<double> diagUpper(n - 2);
    std::vector<double> diagLower(n - 2);
    std::vector<double> vec(n - 1);
    for (size_t i = 0; i < n - 1; i++)
    {
        vec[i] = 6 * (h[i] * (m_points[i + 2].y() - m_points[i + 1].y()) - h[i + 1] * (m_points[i + 1].y() - m_points[i].y())) / (h[i + 1] * h[i] * (h[i + 1] + h[i]));
        diagMain[i] = 2;
    }
    for (size_t i = 0; i < n - 2; i++)
    {
        diagUpper[i] = h[i + 2] / (h[i + 1] + h[i + 2]);
        diagLower[i] = h[i + 1] / (h[i + 1] + h[i + 2]);
    }
    std::vector<double> p(n - 2), q(n - 1);
    p[0] = -diagUpper[0] / diagMain[0];
    for (size_t i = 1; i < n - 2; i++)
    {
        double denom_p = diagLower[i - 1] * p[i - 1] + diagMain[i];
        p[i] = -diagUpper[i] / denom_p;
    }
    q[0] = vec[0] / diagMain[0];
    for (size_t i = 1; i < n - 1; i++)
    {
        double denom_q = diagLower[i - 1] * p[i - 1] + diagMain[i];
        q[i] = (vec[i] - diagLower[i - 1] * q[i - 1]) / denom_q;
    }
    m_c[n - 1] = q[n - 2];
    for (size_t i = n - 2; i > 0; i--)
    {
        m_c[i] = p[i - 1] * m_c[i + 1] + q[i - 1];
    }
    m_d[0] = m_c[1] / h[0];
    m_b[0] = m_c[1] * h[0] / 3 + ((m_points[1].y() - m_points[0].y()) / h[0]);
    for (size_t i = 1; i < n + 1; i++)
    {
        m_a[i] = m_points[i].y();
        m_b[i] = m_c[i] * h[i - 1] / 3 + m_c[i - 1] * h[i - 1] / 6 + ((m_points[i].y() - m_points[i - 1].y()) / h[i - 1]);
        m_d[i] = m_c[i] - m_c[i - 1];
    }
}
