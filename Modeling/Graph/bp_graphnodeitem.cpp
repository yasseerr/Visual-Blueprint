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

#include <Graph/Nodes/bp_eventnode.h>
#include <Graph/Nodes/bp_floatnode.h>
#include <Graph/Nodes/bp_intnode.h>
#include <Graph/Nodes/bp_stringnode.h>

//all the tools should register

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
    BP_Node *retNode = qobject_cast<BP_Node*>(toolNodeMetaObject.newInstance());

//    if(toolType == INTEGER_)
//    {}
//    else if(toolType == STRING)
//    {}
//    else if(toolType == BP_GraFLOAT)
//    {retNode = new BP_FloatNode();}
//    else
//        retNode =  new BP_IntNode();
    retNode->setParent(parent);
    return  retNode;
}

BP_GraphNodeItem *BP_GraphNodeItem::getCoreObjectNode(BP_CoreObject *obj)
{
    if(this->coreObject() == obj) return this;
    foreach (auto child, childItems) {
        auto objNode = child->getCoreObjectNode(obj);
        if(objNode) return objNode;
    }
    return  nullptr;
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
        item->clearChildes();
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


