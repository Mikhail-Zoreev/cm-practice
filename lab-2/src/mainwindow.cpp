#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), p_equations_system_model(nullptr), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    p_solution_model = new SolutionModel;

    ui->frame_tool_bar->setHidden(true);
    ui->table_equations_system->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->table_equations_system->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_solution->setModel(p_solution_model);
    ui->table_solution->setHidden(true);

    connect(ui->action_new_equations_system, &QAction::triggered, this, &MainWindow::newEquationsSystem);
    connect(ui->button_solve, &QAbstractButton::clicked, this, &MainWindow::solve);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newEquationsSystem()
{
    NewEquationsSystemDialog dialog;
    dialog.setModal(true);
    dialog.exec();
    if (dialog.result() == QDialog::Accepted)
    {
        if (p_equations_system_model != nullptr)
        {
            delete p_equations_system_model;
        }
        p_equations_system_model = new EquationsSystemModel(static_cast<size_t>(dialog.resultSize()));
        ui->table_equations_system->setModel(p_equations_system_model);
        ui->frame_tool_bar->setVisible(true);
    }
}

void MainWindow::solve()
{
    ApproximationDialog dialog(p_equations_system_model->size());
    dialog.setModal(true);
    dialog.exec();
    p_equations_system_model->matrix().determinant();
    GaussMethodSolver solver;
    ui->table_solution->setVisible(true);
    p_solution_model->clear();
    p_solution_model->
            push("Kramer", solver.solve(p_equations_system_model->matrix(), p_equations_system_model->column()));
}
