#include "solutionmodel.h"

SolutionModel::SolutionModel(QObject *parent) : QAbstractTableModel(parent)
{

}

void SolutionModel::push(const QString& header, const Column& solution)
{
    bool empty = (m_solutions.size() == 0);
    if (empty)
    {
        beginInsertRows(QModelIndex(), 0, static_cast<int>(solution.size()) - 1);
    }
    beginInsertColumns(QModelIndex(), static_cast<int>(m_solutions.size()),  static_cast<int>(m_solutions.size()));
    m_headers.push_back(header);
    m_solutions.push_back(solution);
    endInsertColumns();
    if (empty)
    {
        endInsertRows();
    }

}

void SolutionModel::clear()
{
    if (m_solutions.size() == 0)
    {
        return;
    }
    beginRemoveRows(QModelIndex(), 0, static_cast<int>(m_solutions[0].size()) - 1);
    beginRemoveColumns(QModelIndex(), 0, static_cast<int>(m_solutions.size()) - 1);
    m_headers.clear();
    m_solutions.clear();
    endRemoveColumns();
    endRemoveRows();
}

int SolutionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (m_solutions.size() != 0)
    {
        return  static_cast<int>(m_solutions[0].size());
    }
    return 0;
}

int SolutionModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_solutions.size());
}

QVariant SolutionModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    return m_solutions[index.column()][index.row()];
}

QVariant SolutionModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if ((role != Qt::DisplayRole) || (orientation == Qt::Vertical))
    {
        return QVariant();
    }
    return m_headers[section];
}
