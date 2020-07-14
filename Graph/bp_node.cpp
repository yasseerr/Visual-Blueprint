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
#include <QMetaClassInfo>
#include <QPainter>

#include <Core/bp_coreobject.h>

#include <Platform/bp_platformmanager.h>

#include<Graph/bp_graphutils.h>

RegisterNodeType(BP_Node)

int BP_Node::nodeCount = 0;
int BP_Node::nodeTypesCount = 0;

BP_Node::BP_Node(QObject *parent):QObject(parent),QGraphicsItem(),m_coreObject(nullptr),m_bounds(0,0,100,50)
{
    nodeId = nodeCount;
    nodeCount++;
    //Graphic item configurations
    this->setFlags(ItemIsMovable|ItemIsSelectable);
}

BP_Node::BP_Node(BP_GraphView *graphView):m_connectedGraph(graphView)
{
    nodeId = nodeCount;
    nodeCount++;
}

QVariant BP_Node::toVariantBP()
{
    //? the static values will be created automaticaly
    QVariantMap retMap;
    retMap["coreObject"] = m_coreObject?coreObject()->toVariantBP():false;
    retMap["numberOfReferenceCalls"] = m_numberOfReferenceCalls;

    return retMap ;
}


BP_Node *BP_Node::Create()
{
    return new BP_Node();
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

void BP_Node::setNumberOfReferenceCalls(int numberOfReferenceCalls)
{
    if (m_numberOfReferenceCalls == numberOfReferenceCalls)
        return;

    m_numberOfReferenceCalls = numberOfReferenceCalls;
    emit numberOfReferenceCallsChanged(m_numberOfReferenceCalls);
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
    if(m_numberOfReferenceCalls == 0){
        m_numberOfReferenceCalls++;
        return FIRST_REFERENCE;
    }
    return "";
}

BP_Node *BP_Node::nextNode()
{
    return nullptr;
}

QString BP_Node::getNodeTypeString()
{
    return "Node";
}

void BP_Node::mapInputFlowToOutput()
{
    //calculate and apply the flow from the input slot to the output one
}

int BP_Node::numberOfReferenceCalls() const
{
    return m_numberOfReferenceCalls;
}

