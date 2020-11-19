#include "splinechart.h"

SplineChart::SplineChart(QGraphicsItem  *parent) : QtCharts::QChart(parent)
{
    this->legend()->hide();

    p_spline_series = new QtCharts::QLineSeries();
    p_spline_series->setColor(QColorConstants::Blue);
    p_points_series = new QtCharts::QScatterSeries();
    p_points_series->setColor(QColorConstants::Blue);
    this->addSeries(p_spline_series);
    this->addSeries(p_points_series);

    p_axis_x = new QtCharts::QValueAxis();
    p_axis_x->setTitleText("x");
    this->addAxis(p_axis_x, Qt::AlignBottom);

    p_axis_y = new QtCharts::QValueAxis();
    p_axis_y->setTitleText("y");
    this->addAxis(p_axis_y, Qt::AlignLeft);

    p_spline_series->attachAxis(p_axis_x);
    p_spline_series->attachAxis(p_axis_y);
    p_points_series->attachAxis(p_axis_x);
    p_points_series->attachAxis(p_axis_y);

    min_x = min_y = 10000;
    max_x = max_y = -10000;
}

SplineChart::~SplineChart()
{
    delete p_spline_series;
    delete p_points_series;
    delete p_axis_x;
    delete p_axis_y;
}

void SplineChart::clear()
{
    p_points_series->clear();
    p_spline_series->clear();
}

void SplineChart::load(const Spline& spline, int width)
{
    p_points_series->clear();
    for (auto i = spline.points().begin(); i != spline.points().end(); i++)
    {
        *p_points_series << *i;

        if (i->x() < min_x)
        {
            min_x = i->x();
        }
        else if (i->x() > max_x)
        {
            max_x = i->x();
        }
        if (i->y() < min_y)
        {
            min_y = i->y();
        }
        else if (i->y() > max_y)
        {
            max_y = i->y();
        }
    }

    p_spline_series->clear();
    if (spline.aviable())
    {
        double delta = (spline.points().rbegin()->x() - spline.points().begin()->x()) / width;

        for (size_t i = 1; i < spline.points().size(); i++)
        {
            for (qreal x = spline.points()[i - 1].x(); x < spline.points()[i].x(); x += delta)
            {
                double value = spline.value(i, x);
                *p_spline_series << QPointF(x, value);
            }
        }
    }

    double delta_x = (max_x - min_x) * 0.1;
    double delta_y = (max_y - min_y) * 0.1;
    p_axis_x->setRange(min_x - delta_x, max_x + delta_x);
    p_axis_y->setRange(min_y - delta_y, max_y + delta_y);

}
