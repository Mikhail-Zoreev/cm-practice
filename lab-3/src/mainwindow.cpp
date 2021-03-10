#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->box_solution->setHidden(true);

    p_system = new SampleEquationSystem;
    p_solution = nullptr;

    connect(ui->button_solve, &QPushButton::clicked, this, &MainWindow::solve);
    connect(ui->button_showplot, &QPushButton::clicked, this, &MainWindow::showPlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::solve()
{
    double a = ui->spinbox_from->value();
    double b = ui->spinbox_to->value();
    double n = ui->spinbox_iterations->value();
    std::array<double, 3> initial_conditions = {
        ui->spinbox_x0->value(),
        ui->spinbox_y0->value(),
        ui->spinbox_z0->value()
    };

    RKMethodSolver solver(p_system);
    p_accurate_solution = new SampleAccurateSolution(a, initial_conditions);
    ui->label_accurate_x->setText(p_accurate_solution->f1Str());
    ui->label_accurate_y->setText(p_accurate_solution->f2Str());
    ui->label_accurate_z->setText(p_accurate_solution->f3Str());
    ui->box_solution->setVisible(true);
    try {
        m_solution_vector = solver.solve(a, b, n, initial_conditions);
    }
    catch (std::runtime_error error)
    {
        QMessageBox::warning(this, "Error", error.what());
        return;
    }

    if (p_solution != nullptr)
    {
        delete p_solution;
    }
    p_solution = new SolutionTableModel(m_solution_vector, ui->table_solution);
    ui->table_solution->setModel(p_solution);
    ui->button_showplot->setEnabled(true);
}

void MainWindow::showPlot()
{
    PlotDialog dialog(m_solution_vector, p_accurate_solution);
    dialog.exec();
}
