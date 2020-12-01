#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), p_equations_system_model(nullptr), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->frame_tool_bar->setHidden(true);

    connect(ui->action_new_equations_system, &QAction::triggered, this, &MainWindow::newEquationsSystem);
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
