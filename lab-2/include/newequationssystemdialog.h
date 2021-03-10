#pragma once

#include <QDialog>

namespace Ui {
    class NewEquationsSystemDialog;
}

class NewEquationsSystemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewEquationsSystemDialog(QWidget *parent = nullptr);
    ~NewEquationsSystemDialog();

    int resultSize();

private:
    Ui::NewEquationsSystemDialog *ui;
};

