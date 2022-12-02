#ifndef MODEL_H
#define MODEL_H
#include <QObject>

class model
{
public:
    static QVector<QVector<QString>> table;
    void setModel(QVector<QVector<QString>> tb){ table=tb;}
    QVector<QVector<QString>> getModel(){ return table;}
    model();
};

#endif // MODEL_H
