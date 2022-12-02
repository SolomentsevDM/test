#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include<QAbstractTableModel>
#include "Socket.h"
#include <qcolor.h>
class TableModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    Socket *sct=new Socket(this);

public:
    QVector<QVector<QString>> table;
    bool ready=false;
    explicit TableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex & = QModelIndex()) const override;

    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    Q_INVOKABLE QVariant getdata(int row,int column) const;



    QHash<int, QByteArray> roleNames() const override;
    void addPerson();
public slots:
    void gettable(QVector<QVector<QString>> table);
    void ErrorSct(QString err);
signals:
    void getError(QString err);
};

#endif // TABLEMODEL_H
