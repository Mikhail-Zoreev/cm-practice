#pragma once

#include <QAbstractTableModel>

#include <string>

#include "matrix.h"


class EquationsSystemModel : public QAbstractTableModel
{
    Q_OBJECT

protected:
    size_t m_size;
    Matrix m_matrix;
    Column m_column;

public:
    EquationsSystemModel(size_t size,QObject *parent = nullptr);

    const Matrix &matrix() const;
    const Column &column() const;

protected:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};
