#include "solutiontablemodel.h"

SolutionTableModel::SolutionTableModel(const std::vector<std::array<double, 4>>& solutions, QObject *parent)
    :QAbstractTableModel(parent), m_solutions(solutions)
{
    m_count = static_cast<int>(m_solutions.size());
}

int SolutionTableModel::rowCount(const QModelIndex &parent) const
{
    return m_count;
}

int SolutionTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant SolutionTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    int row = index.row();
    int column = index.column();
    return m_solutions[row][column];
}

QVariant SolutionTableModel::headerData(int column, Qt::Orientation orientatioln, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    if (orientatioln == Qt::Vertical)
    {
        return column + 1;
    }
    switch (column) {
        case 0:
        {
            return "x";
        }
        case 1:
        {
            return "y";
        }
        case 2:
        {
            return "z";
        }
        case 3:
        {
            return "t";
        }
    }
    return "...";
}
