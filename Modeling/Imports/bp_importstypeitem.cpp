/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_importstypeitem.h"

#include <QIcon>
#include <QVariant>

BP_ImportsTypeItem::BP_ImportsTypeItem(QString _name,BP_ImportsItem *parentItem,QObject *parent):
    BP_ImportsItem(parentItem,parent)
{
    m_name  = _name;
    setIsInspectable(false);

}

QVariant BP_ImportsTypeItem::getIconVariant()
{
    QIcon itemIcon(":/Data/Images/DefaultIcon/class.png");
    return QVariant::fromValue(itemIcon);
}
