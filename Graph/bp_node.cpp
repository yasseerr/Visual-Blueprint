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

std::vector<QMetaObject>* BP_Node::nodeTypesVector = new std::vector<QMetaObject>();
//QMap<QString,const QMetaObject*>* BP_Node::nodesMap = new  QMap<QString,const QMetaObject*>;
//QList<QMetaObject>* BP_Node::nodeTypesList = initializeNodesTypes();
int BP_Node::nodeCount = 0;
//QMetaType* BP_Node::nodeTypesArray =QMetaObject[100];
//QMetaObject* BP_Node::nodeTypesArray = new QMetaObject[100];
//int BP_Node::nodeTypesCount = 1;
//QMap<QString,BP_Node* (*)()>* BP_Node::nodesMap = new  QMap<QString,BP_Node* (*)()>;
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

QList<QMetaObject>* BP_Node::initializeNodesTypes()
{
    //TODO setup the number of nodes types as parameter
    QList<QMetaObject>* ret = new QList<QMetaObject>();
    for (int i = 0; i < 100; ++i) {
        ret->append(QMetaObject());
    }
    return ret;
}

int BP_Node::setupNodeType(QMetaObject metaObj)
{
    //nodesMap->insert(metaObj);
    //nodeTypesList->append(metaObj);
    //nodeTypesArray[nodeTypesCount] = &metaObj;
    nodeTypesVector->push_back(metaObj);
    //nodeTypesList->reserve(200);
    qDebug("testing the creation of instances");
    BP_Node *obj1 = qobject_cast<BP_Node*>(metaObj.newInstance());
    qDebug()<< "this is the new node: "<< obj1->getNodeTypeString();
    return nodeTypesCount + 1;
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

QString BP_Node::getNodeTypeString()
{
    return "Node";
}

