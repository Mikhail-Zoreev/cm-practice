#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), p_equations_system_model(nullptr), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    p_solution_model = new SolutionModel;

    m_solvers.push_back(new GaussMethodSolver());
    m_solvers.push_back(new KramerMethodSolver());
    m_solvers.push_back(new LUDecompositionMethodSolver());
    m_solvers.push_back(new SeidelMethodSolver());
    m_solvers.push_back(new SimpleIterationsMethodSolver());
    m_solvers.push_back(new UpperRelaxationMethodSolver());

    ui->frame_tool_bar->setHidden(true);
    ui->table_equations_system->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->table_equations_system->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_solution->setModel(p_solution_model);
    ui->table_solution->setHidden(true);
    for (auto solver : m_solvers)
    {
        ui->combobox_method->addItem(QString::fromStdString(solver->name()));
    }

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
    EquationsSystemSolver *solver = m_solvers[ui->combobox_method->currentIndex()];
    Column column(p_equations_system_model->size());
    if (solver->approximate())
    {
        ApproximationDialog dialog(p_equations_system_model->size());
        dialog.setModal(true);
        dialog.exec();
        if(dialog.result() == QDialog::Accepted)
        {
            column = dialog.resultColumn();
        }
        else
        {
            return;
        }
    }

    p_equations_system_model->matrix().determinant();
    ui->table_solution->setVisible(true);
    p_solution_model->clear();
    p_solution_model->push(QString::fromStdString(solver->name()), solver->solve(p_equations_system_model->matrix(),
                                                  p_equations_system_model->column(), column, 0.1));
}
