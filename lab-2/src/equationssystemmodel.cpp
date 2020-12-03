#include "equationssystemmodel.h"


EquationsSystemModel::EquationsSystemModel(size_t size, QObject *parent) : QAbstractTableModel(parent), m_size(size),
    m_matrix(size), m_column(size)
{

}

size_t EquationsSystemModel::size() const
{
    return m_size;
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
    return static_cast<int>(m_size);
}

int EquationsSystemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_size) + 1;
}

QVariant EquationsSystemModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    return (static_cast<size_t>(index.column()) < m_size) ? m_matrix(index.column(), index.row()) : m_column[index.row()];
}

bool EquationsSystemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
    {
        return false;
    }
    bool ok = false;
    double new_value = value.toDouble(&ok);
    if (ok)
    {
        if (static_cast<size_t>(index.column()) < m_size)
        {
            m_matrix(index.column(), index.row()) = new_value;
        }
        else
        {
            m_column[index.row()] = new_value;
        }
        emit dataChanged(index, index);
    }
    return ok;
}

Qt::ItemFlags EquationsSystemModel::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
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
