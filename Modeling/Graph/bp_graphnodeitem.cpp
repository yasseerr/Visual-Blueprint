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

#include <Graph/Nodes/bp_intnode.h>
#include <Graph/Nodes/bp_stringnode.h>

BP_GraphNodeItem::BP_GraphNodeItem(BP_GraphNodeItem *parentItem,QObject *parent,QString displayName) : QObject(parent),m_parentItem(parentItem),m_displayName(displayName),m_coreObject(nullptr),m_isTool(false)
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

BP_Node *BP_GraphNodeItem::createToolNode(QObject *parent)
{
    BP_Node *retNode = nullptr;
    if(toolType == INTEGER)
        retNode = new BP_IntNode();
    else if(toolType == STRING)
        retNode = new BP_StringNode();
    else
        retNode =  new BP_IntNode();
    retNode->setParent(parent);
    return  retNode;
}

BP_CoreObject *BP_GraphNodeItem::coreObject() const
{
    return m_coreObject;
}

bool BP_GraphNodeItem::isTool() const
{
    return m_isTool;
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

void BP_GraphNodeItem::setIsTool(bool isTool)
{
    if (m_isTool == isTool)
        return;

    m_isTool = isTool;
    emit isToolChanged(m_isTool);
}


