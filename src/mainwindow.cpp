#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    p_chart = new SplineChart();
    Spline spline;
    spline.insert(QPointF(1, 1));
    spline.insert(QPointF(0.5, 0.3));
    spline.insert(QPointF(0.6, 0.3));
    p_chart->load(spline);
    ui->chart_view->setChart(p_chart);
}

MainWindow::~MainWindow()
{
    delete p_chart;

    delete ui;
}

