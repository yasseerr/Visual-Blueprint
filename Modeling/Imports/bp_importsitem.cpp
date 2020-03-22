/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_importsitem.h"

#include <Modeling/importsmodel.h>

BP_ImportsItem::BP_ImportsItem(BP_ImportsItem *parentItem,QObject *parent) : QObject(parent),
  m_parentItem(parentItem)
{
    if(m_parentItem != nullptr){
        m_parentItem->childItems.append(this);
        if(m_parentItem->m_model != nullptr)
            m_model = m_parentItem->m_model;
    }

}

QStringList BP_ImportsItem::getImportHierarchy()
{
    QStringList retList;
    BP_ImportsItem *hierarchtStep = this;
    while (hierarchtStep != nullptr) {
        retList << hierarchtStep->m_name;
        hierarchtStep = hierarchtStep->m_parentItem;
        if(hierarchtStep == m_model->rootItem())
            break;
    }
    return  retList;
}

QVariant BP_ImportsItem::getIconVariant()
{
    QIcon itemIcon(":/Data/Images/DefaultIcon/hardware-processor.png");
    return QVariant::fromValue(itemIcon);
}
