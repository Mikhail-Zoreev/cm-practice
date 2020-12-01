#pragma once

#include <QMainWindow>

#include "equationssystemmodel.h"
#include "newequationssystemdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    EquationsSystemModel *p_equations_system_model;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected slots:
    void newEquationsSystem();
};
