/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_importsvariableitem.h"

#include <QIcon>
#include <QVariant>

BP_ImportsVariableItem::BP_ImportsVariableItem(QString _name,BP_ImportsItem *parentItem,QObject *parent):
    BP_ImportsItem(parentItem,parent)
{
    m_name = _name;
    setIsInspectable(false);
}

QVariant BP_ImportsVariableItem::getIconVariant()
{
    QIcon itemIcon(":/Data/Images/DefaultIcon/3D-Cube.png");
    return QVariant::fromValue(itemIcon);
}
