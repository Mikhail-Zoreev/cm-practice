#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    p_chart = new SplineChart();
    ui->chart_view->setChart(p_chart);
}

MainWindow::~MainWindow()
{
    delete p_chart;

    delete ui;
}

