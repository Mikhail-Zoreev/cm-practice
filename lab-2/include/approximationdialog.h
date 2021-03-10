#pragma once

#include <QDialog>

#include "approximationtablemodel.h"
#include "matrix.h"

namespace Ui {
    class approximationdialog;
}

class ApproximationDialog : public QDialog
{
    Q_OBJECT

protected:
    ApproximationTableModel *p_approximation_table_model;

public:
    explicit ApproximationDialog(size_t size, QWidget *parent = nullptr);
    ~ApproximationDialog();

    const Column &resultColumn() const;
    double resultEpsilon() const;

private:
    Ui::approximationdialog *ui;
};

