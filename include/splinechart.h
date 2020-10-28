#pragma once

#include <QChart>
#include <QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>

class SplineChart : public QtCharts::QChart
{
protected:
    QtCharts::QLineSeries    *p_spline_series;
    QtCharts::QScatterSeries *p_points_series;

    QtCharts::QValueAxis *p_axis_x;
    QtCharts::QValueAxis *p_axis_y;

public:
    SplineChart(QGraphicsItem *parent = nullptr);
    ~SplineChart();
};
