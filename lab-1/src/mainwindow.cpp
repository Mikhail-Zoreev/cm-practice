#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_add_point, &QAction::triggered, this, &MainWindow::showAddPointDialog);
    connect(ui->action_help, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->action_clear, &QAction::triggered, this, &MainWindow::clearChart);

    p_chart = new SplineChart();
    ui->chart_view->setChart(p_chart);
}

MainWindow::~MainWindow()
{
    delete p_chart;

    delete ui;
}

void MainWindow::clearChart()
{
    p_chart->clear();
    m_spline.clear();
}

void MainWindow::showAddPointDialog()
{
    PointDialog dialog;
    dialog.exec();
    if (dialog.result() == QDialog::Accepted)
    {
        m_spline.insert(dialog.resultPointF());
        p_chart->load(m_spline, ui->chart_view->width());
    }
}

void MainWindow::showHelpDialog()
{
    HelpDialog dialog;
    dialog.exec();
}
