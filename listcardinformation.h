#ifndef LISTCARDINFORMATION_H
#define LISTCARDINFORMATION_H

#include <QObject>
#include <QVector>

#include "cardinformation.h"

class ListCardInformation : public QObject
{
    Q_OBJECT
public:
    explicit ListCardInformation(QObject *parent = nullptr);

    QVector<CardInformation> * getListAllCardInformation();
    void setListAllCardInformation(QVector<CardInformation> *);

signals:

private:
    QVector<CardInformation> *listAllCardInformation;

};

#endif // LISTCARDINFORMATION_H
