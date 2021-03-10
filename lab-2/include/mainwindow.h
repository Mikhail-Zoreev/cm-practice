#pragma once

#include <QMainWindow>

#include <chrono>
#include <stdexcept>
#include <vector>

#include <QMessageBox>

#include "approximationdialog.h"
#include "equationssystemmodel.h"
#include "equationssystemsolver.h"
#include "gaussmethodsolver.h"
#include "kramermethodsolver.h"
#include "ludecompositionmethodsolver.h"
#include "newequationssystemdialog.h"
#include "seidelmethodsolver.h"
#include "simpleiterationsmethodsolver.h"
#include "solutionmodel.h"
#include "upperrelaxationmethodsolver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    EquationsSystemModel *p_equations_system_model;
    SolutionModel *p_solution_model;

    std::vector<EquationsSystemSolver*> m_solvers;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected slots:
    void newEquationsSystem();
    void solve();
};
