#include "plotdialog.h"
#include "ui_plotdialog.h"

PlotDialog::PlotDialog(const std::vector<std::array<double, 4>>& solution, AbstractAccurateSolution* accurate_solution, QWidget *parent)
    : QDialog(parent), ui(new Ui::PlotDialog)
{
    ui->setupUi(this);
    int steps_count = static_cast<int>(solution.size());
    QVector<double> t(steps_count);
    QVector<double> x(steps_count), y(steps_count), z(steps_count);
    QVector<double> x_accurate(steps_count), y_accurate(steps_count), z_accurate(steps_count);
    for (int i = 0; i < steps_count; i++)
    {
        t[i] = solution[i][3];
        x[i] = solution[i][0];
        y[i] = solution[i][1];
        z[i] = solution[i][2];
        x_accurate[i] = accurate_solution->f1(t[i]);
        y_accurate[i] = accurate_solution->f2(t[i]);
        z_accurate[i] = accurate_solution->f3(t[i]);
    }

    ui->plot_x->addGraph();
    ui->plot_x->graph(0)->setData(t, x);
    ui->plot_x->graph(0)->setPen(QPen(Qt::blue));
    ui->plot_x->addGraph();
    ui->plot_x->graph(1)->setData(t, x_accurate);
    ui->plot_x->graph(1)->setPen(QPen(Qt::green));
    ui->plot_x->xAxis->setLabel("t");
    ui->plot_x->yAxis->setLabel("x");
    ui->plot_x->graph(0)->rescaleAxes();
    ui->plot_x->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot_x->replot();

    ui->plot_y->addGraph();
    ui->plot_y->graph(0)->setData(t, y);
    ui->plot_y->graph(0)->setPen(QPen(Qt::blue));
    ui->plot_y->addGraph();
    ui->plot_y->graph(1)->setData(t, y_accurate);
    ui->plot_y->graph(1)->setPen(QPen(Qt::green));
    ui->plot_y->xAxis->setLabel("t");
    ui->plot_y->yAxis->setLabel("y");
    ui->plot_y->graph(0)->rescaleAxes();
    ui->plot_y->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot_y->replot();

    ui->plot_z->addGraph();
    ui->plot_z->graph(0)->setData(t, z);
    ui->plot_z->graph(0)->setPen(QPen(Qt::blue));
    ui->plot_z->addGraph();
    ui->plot_z->graph(1)->setData(t, z_accurate);
    ui->plot_z->graph(1)->setPen(QPen(Qt::green));
    ui->plot_z->xAxis->setLabel("t");
    ui->plot_z->yAxis->setLabel("z");
    ui->plot_z->graph(0)->rescaleAxes();
    ui->plot_z->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot_z->replot();
}

PlotDialog::~PlotDialog()
{
    delete ui;
}
