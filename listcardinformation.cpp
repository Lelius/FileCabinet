#include "listcardinformation.h"

ListCardInformation::ListCardInformation(QObject *parent) : QObject(parent)
{

}

QVector<CardInformation> ListCardInformation::getListAllCardInformation()
{
    return listAllCardInformation;
}

void ListCardInformation::setListAllCardInformation(const QVector<CardInformation> &list)
{
    listAllCardInformation = list;
}
