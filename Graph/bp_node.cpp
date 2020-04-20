/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_graphview.h"
#include "bp_node.h"

#include <QPainter>

#include <Core/bp_coreobject.h>

BP_Node::BP_Node(QObject *parent):QObject(parent),m_coreObject(nullptr)
{

}

BP_Node::BP_Node(BP_GraphView *graphView):m_connectedGraph(graphView)
{

}

BP_CoreObject *BP_Node::coreObject() const
{
    return m_coreObject;
}

BP_GraphView *BP_Node::connectedGraph() const
{
    return m_connectedGraph;
}

void BP_Node::setCoreObject(BP_CoreObject *coreObject)
{
    if (m_coreObject == coreObject)
        return;

    m_coreObject = coreObject;
    emit coreObjectChanged(m_coreObject);
}

void BP_Node::setConnectedGraph(BP_GraphView *connectedGraph)
{
    if (m_connectedGraph == connectedGraph)
        return;

    m_connectedGraph = connectedGraph;
    emit connectedGraphChanged(m_connectedGraph);
}

QRectF BP_Node::boundingRect() const
{
    return  QRectF(0,0,100,100);
}

void BP_Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->drawRect(boundingRect());
    if(m_coreObject != nullptr)
        painter->drawText(0,0,m_coreObject->name());
}
