/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_graphnodeitem.h"

BP_GraphNodeItem::BP_GraphNodeItem(BP_GraphNodeItem *parentItem,QObject *parent,QString displayName) : QObject(parent),m_parentItem(parentItem),m_displayName(displayName),m_coreObject(nullptr)
{
    if(m_parentItem != nullptr){
        m_parentItem->childItems.append(this);
        if(m_parentItem->m_model != nullptr)
            m_model = m_parentItem->m_model;
    }
}

BP_GraphNodeItem::~BP_GraphNodeItem()
{
    foreach (auto item, childItems) {
        childItems.removeOne(item);
        item->deleteLater();
    }
}

BP_CoreObject *BP_GraphNodeItem::coreObject() const
{
    return m_coreObject;
}

void BP_GraphNodeItem::setCoreObject(BP_CoreObject *coreObject)
{
    if (m_coreObject == coreObject)
        return;

    m_coreObject = coreObject;
    emit coreObjectChanged(m_coreObject);
}

void BP_GraphNodeItem::clearChildes()
{
    foreach (auto item, childItems) {
        childItems.removeOne(item);
        item->deleteLater();
    }
}


