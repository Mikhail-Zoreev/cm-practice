#pragma once

#include <QAbstractTableModel>

#include "matrix.h"

class ApproximationTableModel : public QAbstractTableModel
{
    Q_OBJECT;

protected:
    Column m_column;

public:
    explicit ApproximationTableModel(size_t size, QObject *parent = nullptr);
    ~ApproximationTableModel() = default;

    const Column &column() const;

protected:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};
