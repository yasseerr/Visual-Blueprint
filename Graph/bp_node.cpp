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

#include <QDebug>
#include <QPainter>

#include <Core/bp_coreobject.h>

#include <Platform/bp_platformmanager.h>

BP_Node::BP_Node(QObject *parent):QObject(parent),QGraphicsItem(),m_coreObject(nullptr),m_bounds(0,0,100,50)
{

    //Graphic item configurations
    this->setFlags(ItemIsMovable|ItemIsSelectable);
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
    calculateBounds();
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
    return  m_bounds;
}

void BP_Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->drawRect(boundingRect());
    if(m_coreObject != nullptr)
        painter->drawText(0,0,m_coreObject->name());
}

void BP_Node::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsItem::dragMoveEvent(event);
    //TODO only update the links for optimisation
    //qDebug() << "dragged";
    //scene()->update();
}

void BP_Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    scene()->update();
}

void BP_Node::calculateBounds()
{
    if(m_coreObject != nullptr){
        m_bounds = QFontMetrics(QFont()).boundingRect(m_coreObject->name());
    }
}

QString BP_Node::renderNode(BP_PlatformManager *platform)
{
    return "";
}

BP_Node *BP_Node::nextNode()
{
    return nullptr;

}
