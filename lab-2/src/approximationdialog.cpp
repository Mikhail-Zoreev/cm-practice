#include "approximationdialog.h"
#include "ui_approximationdialog.h"

ApproximationDialog::ApproximationDialog(size_t size, QWidget *parent) : QDialog(parent), ui(new Ui::approximationdialog)
{
    ui->setupUi(this);

    p_approximation_table_model = new ApproximationTableModel(size);

    ui->table_approximation->setModel(p_approximation_table_model);
    ui->table_approximation->horizontalHeader()->setHidden(true);
    ui->table_approximation->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->table_approximation->setSelectionMode(QAbstractItemView::SingleSelection);
}

ApproximationDialog::~ApproximationDialog()
{
    delete ui;
    if (p_approximation_table_model != nullptr)
    {
        delete p_approximation_table_model;
    }
}

const Column &ApproximationDialog::resultColumn() const
{
    return p_approximation_table_model->column();
}
