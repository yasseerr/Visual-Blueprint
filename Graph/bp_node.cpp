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
#include <QVariantMap>
#include <bp_utils.h>

#include <Core/bp_coreobject.h>

#include <Platform/bp_platformmanager.h>

#include<Graph/bp_graphutils.h>

RegisterNodeType(BP_Node)

int BP_Node::nodeCount = 0;
int BP_Node::nodeTypesCount = 0;

BP_Node::BP_Node(QObject *parent):QObject(parent)
  ,QGraphicsItem()
  ,m_coreObject(nullptr)
  ,m_bounds(0,0,100,50)
  ,m_noFlowNode(true)
  ,m_clotureNode(nullptr)
{
    nodeId = nodeCount;
    BP_GraphUtils::getInstance()->registerNodeID(nodeId,this);
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
    retMap["nodeId"] = nodeId;
    retMap["coreObject"] = m_coreObject?coreObject()->toVariantBP():false;
    retMap["numberOfReferenceCalls"] = m_numberOfReferenceCalls;
    retMap["scenePosX"] = pos().x();
    retMap["scenePosY"] = pos().y();

    return retMap ;
}

void BP_Node::fromVariant(QVariant var)
{
    QVariantMap varMap =var.toMap();
    
    nodeId = varMap["nodeId"].toInt();
    //TODO clear the previous node id
    BP_GraphUtils::getInstance()->registerNodeID(nodeId,this);
//    if(varMap["coreObject"].type() == QVariant::Bool){
//        if(!varMap["coreObject"].toBool()) setCoreObject(nullptr);
//    }
    if(varMap["coreObject"].toMap()["isImported"].toBool()){
        auto coreObjects = BP_Utils::instance()->coreObjectsMap.values(varMap["coreObject"].toMap()["name"].toString());
        //TODO compare the objects hierarchy when multiple objects are found
        foreach (auto coreObject, coreObjects) {
            if(coreObject == this->coreObject()) continue;
            qDebug()<<"core Object found " << coreObject->name() ;
            setCoreObject(coreObject);
        }
    }
    //TODO investigate the nessecity to load numverOfReferenceCalls
    setPos(varMap["scenePosX"].toFloat(),varMap["scenePosY"].toFloat());
}

void BP_Node::updateSlotsBranches(BP_Slot *slot)
{
    //to be reimplemented
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

void BP_Node::setNoFlowNode(bool noFlowNode)
{
    if (m_noFlowNode == noFlowNode)
        return;

    m_noFlowNode = noFlowNode;
    emit noFlowNodeChanged(m_noFlowNode);
}

void BP_Node::setOriginalBranches(QList<BP_FrameBranch *> originalBranches)
{
    if (m_originalBranches == originalBranches)
        return;

    m_originalBranches = originalBranches;
    emit originalBranchesChanged(m_originalBranches);
}

void BP_Node::setSubBranches(QList<BP_FrameBranch *> subBranches)
{
    if (m_subBranches == subBranches)
        return;

    m_subBranches = subBranches;
    emit subBranchesChanged(m_subBranches);
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

bool BP_Node::noFlowNode() const
{
    return m_noFlowNode;
}

QList<BP_FrameBranch *> BP_Node::originalBranches() const
{
    return m_originalBranches;
}

QList<BP_FrameBranch *> BP_Node::subBranches() const
{
    return m_subBranches;
}

