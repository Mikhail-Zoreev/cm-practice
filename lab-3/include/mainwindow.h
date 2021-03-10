#pragma once

#include <QMainWindow>

#include <array>

#include <QMessageBox>

#include "abstractaccuratesolution.h"
#include "abstractequationsystem.h"
#include "plotdialog.h"
#include "rkmethodsolver.h"
#include "sampleaccuratesolution.h"
#include "sampleequationsystem.h"
#include "solutiontablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    AbstractEquationSystem *p_system;
    SolutionTableModel *p_solution;
    std::vector<std::array<double, 4>> m_solution_vector;
    AbstractAccurateSolution *p_accurate_solution;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void solve();
    void showPlot();
};
