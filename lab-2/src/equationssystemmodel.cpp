#include "equationssystemmodel.h"


EquationsSystemModel::EquationsSystemModel(size_t size, QObject *parent) : QAbstractTableModel(parent), m_size(size),
    m_matrix(size), m_column(size)
{

}

const Matrix &EquationsSystemModel::matrix() const
{
    return m_matrix;
}

const Column &EquationsSystemModel::column() const
{
    return m_column;
}

int EquationsSystemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_size;
}

int EquationsSystemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_size + 1;
}

QVariant EquationsSystemModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    return (static_cast<size_t>(index.column()) < m_size) ? m_matrix(index.row(), index.column()) : m_column[index.row()];
}

QVariant EquationsSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    if (orientation == Qt::Vertical)
    {
        return QString::fromStdString(std::to_string(section));
    }
    if (static_cast<size_t>(section) == m_size)
    {
        return "b";
    }
    return "x" + QString::fromStdString(std::to_string(section));
}
