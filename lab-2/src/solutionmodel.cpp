#include "solutionmodel.h"

SolutionModel::SolutionModel(QObject *parent) : QAbstractTableModel(parent)
{

}

void SolutionModel::push(const QString& header, const Column& solution, int64_t duration)
{
    bool empty = (m_solutions.size() == 0);
    if (empty)
    {
        beginInsertRows(QModelIndex(), 0, static_cast<int>(solution.size()));
    }
    beginInsertColumns(QModelIndex(), static_cast<int>(m_solutions.size()),  static_cast<int>(m_solutions.size()));
    m_headers.push_back(header);
    m_solutions.push_back(solution);
    m_durations.push_back(duration);
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
    beginRemoveRows(QModelIndex(), 0, static_cast<int>(m_solutions[0].size()));
    beginRemoveColumns(QModelIndex(), 0, static_cast<int>(m_solutions.size()) - 1);
    m_headers.clear();
    m_solutions.clear();
    m_durations.clear();
    endRemoveColumns();
    endRemoveRows();
}

int SolutionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (m_solutions.size() != 0)
    {
        return  static_cast<int>(m_solutions[0].size()) + 1;
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
    if (static_cast<size_t>(index.row()) < m_solutions[index.column()].size())
    {
        return m_solutions[index.column()][index.row()];
    }
    else
    {
        return m_durations[index.column()];
    }
}

QVariant SolutionModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if ((role != Qt::DisplayRole))
    {
        return QVariant();
    }
    else if (orientation == Qt::Horizontal)
    {
        return m_headers[section];
    }
    else if (m_headers.size() != 0)
    {
        if (static_cast<size_t>(section) < m_solutions[0].size())
        {
            return "x" + QString::fromStdString(std::to_string(section));
        }
        else
        {
            return "time (ms)";
        }
    }
    return QVariant();
}
