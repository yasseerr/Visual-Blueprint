/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_importsfunctionitem.h"

#include <QIcon>
#include <QVariant>

BP_ImportsFunctionItem::BP_ImportsFunctionItem(QString _name,BP_ImportsItem *parentItem,QObject *parent):
    BP_ImportsItem(parentItem,parent)
{
    m_name = _name;
    setIsInspectable(false);
}

QVariant BP_ImportsFunctionItem::getIconVariant()
{
    QIcon itemIcon(":/Data/Images/DefaultIcon/MD-flash.png");
    return QVariant::fromValue(itemIcon);
}

void BP_ImportsFunctionItem::importItem()
{

}
