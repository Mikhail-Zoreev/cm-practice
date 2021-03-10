#pragma once

#include <QDialog>

#include <array>
#include <vector>

#include "qcustomplot.h"

namespace Ui {
    class PlotDialog;
}

class PlotDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::PlotDialog *ui;

public:
    explicit PlotDialog(const std::vector<std::array<double, 4>>& solution, QWidget *parent = nullptr);
    ~PlotDialog();
};

