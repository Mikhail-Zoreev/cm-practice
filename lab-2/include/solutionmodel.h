#pragma once

#include <QAbstractTableModel>

#include <vector>

#include <QString>

#include "matrix.h"

class SolutionModel : public QAbstractTableModel
{
    Q_OBJECT

protected:
    std::vector<QString> m_headers;
    std::vector<Column> m_solutions;

public:
    SolutionModel(QObject *parent = nullptr);
    ~SolutionModel() = default;

    void push(const QString& header, const Column& solution);

protected:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};
