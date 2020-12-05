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
    ui->combobox_method->addItem("All");

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
    p_solution_model->clear();
    int index = ui->combobox_method->currentIndex();
    if (index != static_cast<int>(m_solvers.size()))
    {
        Column column(p_equations_system_model->size());
        double epsilon = 0;
        EquationsSystemSolver *solver = m_solvers[index];
        if (solver->approximate())
        {
            ApproximationDialog dialog(p_equations_system_model->size());
            dialog.setModal(true);
            dialog.exec();
            if(dialog.result() == QDialog::Accepted)
            {
                column  = dialog.resultColumn();
                epsilon = dialog.resultEpsilon();
            }
            else
            {
                return;
            }
        }
        try
        {
            auto begin_time = std::chrono::steady_clock::now();
            Column result = solver->solve(p_equations_system_model->matrix(), p_equations_system_model->column(),
                                          column, epsilon);
            auto end_time = std::chrono::steady_clock::now();
            p_solution_model->push(QString::fromStdString(solver->name()), result,
                                   std::chrono::duration_cast<std::chrono::microseconds>(end_time
                                                                                         - begin_time).count());
            ui->table_solution->setVisible(true);
        }
        catch (std::runtime_error& error)
        {
            QMessageBox::warning(this, "Error", error.what());
            return;
        }

    }
    else
    {
        Column column(p_equations_system_model->size());
        double epsilon = 0;
        ApproximationDialog dialog(p_equations_system_model->size());
        dialog.setModal(true);
        dialog.exec();
        if(dialog.result() == QDialog::Accepted)
        {
            column = dialog.resultColumn();
            epsilon = dialog.resultEpsilon();
        }
        else
        {
            return;
        }
        ui->table_solution->setVisible(true);
        for (auto solver : m_solvers)
        {
            try
            {
                auto begin_time = std::chrono::steady_clock::now();
                Column result = solver->solve(p_equations_system_model->matrix(), p_equations_system_model->column(),
                                              column, epsilon);
                auto end_time = std::chrono::steady_clock::now();
                p_solution_model->push(QString::fromStdString(solver->name()), result,
                                       std::chrono::duration_cast<std::chrono::microseconds>(end_time
                                                                                             - begin_time).count());
            }
            catch (std::runtime_error& error)
            {
                QMessageBox::warning(this, "Error", error.what());
                return;
            }
        }
    }

}
