#include "approximationtablemodel.h"

ApproximationTableModel::ApproximationTableModel(size_t size, QObject *parent) : QAbstractTableModel(parent),
    m_column(size)
{

}

const Column &ApproximationTableModel::column() const
{
    return m_column;
}

int ApproximationTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_column.size());
}

int ApproximationTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant ApproximationTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    return m_column[index.row()];
}

bool ApproximationTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
    {
        return false;
    }
    bool ok = false;
    double new_value = value.toDouble(&ok);
    if (ok)
    {
        m_column[index.row()] = new_value;
        emit dataChanged(index, index);
    }
    return ok;
}

Qt::ItemFlags ApproximationTableModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QVariant ApproximationTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    if (orientation == Qt::Vertical)
    {
        return "x" + QString::fromStdString(std::to_string(section));
    }
    return QVariant();
}
