#include "TableModel.h"
#include<QDebug>
#include<QTcpSocket>
#include <QtQuick>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    connect(sct,SIGNAL(isdone(QVector<QVector<QString>>)),this,SLOT(gettable(QVector<QVector<QString>>)));
    connect(sct,SIGNAL(Error(QString)),this,SLOT(ErrorSct(QString)));
}

int TableModel::rowCount(const QModelIndex &) const
{
    return this->table.size();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return this->table.size()>0? this->table.at(0).size():0;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return table.at(index.row()).at(index.column());
    default:
        break;
    }

    return QVariant();
}

Q_INVOKABLE QVariant TableModel::getdata(int row,int column) const
{
    return table.at(row).at(column);
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}
void TableModel::gettable(QVector<QVector<QString> > table)
{
    this->beginResetModel();
    this->table=table;
    ready=true;
    this->endResetModel();
}

void TableModel::ErrorSct(QString err)
{
    emit getError(err);
}
