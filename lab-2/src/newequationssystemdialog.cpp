#include "newequationssystemdialog.h"
#include "ui_newequationssystemdialog.h"

NewEquationsSystemDialog::NewEquationsSystemDialog(QWidget *parent) : QDialog(parent), ui(new Ui::NewEquationsSystemDialog)
{
    ui->setupUi(this);
}

NewEquationsSystemDialog::~NewEquationsSystemDialog()
{
    delete ui;
}

int NewEquationsSystemDialog::resultSize()
{
    return ui->spinbox_size->value();
}
