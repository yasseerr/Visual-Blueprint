/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_variablenode.h"

#include <Graph/Slots/bp_dataslot.h>

#include <qpainter.h>

#include <Core/bp_parameter.h>
#include <Core/bp_variable.h>

#include <Graph/bp_graphutils.h>


RegisterNodeType(BP_VariableNode)
//int BP_VariableNode::nodeTypeID = BP_VariableNode::setupNodeType(X::staticMetaObject);

BP_VariableNode::BP_VariableNode():BP_Node(),m_variableObject(nullptr),m_outputSlot(new BP_DataSlot(this))
{
    m_outputSlot->setParentItem(this);
    m_outputSlot->setIsOutput(true);
    m_outputSlot->setShowName(false);
}

QVariant BP_VariableNode::toVariantBP()
{
    QVariantMap retMap = BP_Node::toVariantBP().toMap();
    retMap["type"] = getNodeTypeString();
    retMap["variableObject"] =m_variableObject?variableObject()->toVariantBP():false;
    retMap["outputSlot"] = m_outputSlot->toVariantBP();
    return retMap;
}

void BP_VariableNode::calculateBounds()
{
    BP_Node::calculateBounds();
    m_bounds.setHeight(30);
    m_bounds.setWidth(m_bounds.width()+30);
    m_outputSlot->setPos(m_outputSlot->mapFromParent(m_bounds.width()-17,-7));
}


void BP_VariableNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //BP_Node::paint(painter,option,widget);
    //painter->setPen(Qt::);
    painter->setBrush(Qt::GlobalColor::green);
    painter->drawRoundedRect(boundingRect(),2,2);
    painter->drawText(5,7,m_variableObject->name());
}

BP_Variable *BP_VariableNode::variableObject() const
{
    return m_variableObject;
}

BP_DataSlot *BP_VariableNode::outputSlot() const
{
    return m_outputSlot;
}

QString BP_VariableNode::getNodeTypeString()
{
    return "Variable";
}

void BP_VariableNode::setVariableObject(BP_Variable *variableObject)
{
    if (m_variableObject == variableObject)
        return;
    m_variableObject = variableObject;

    BP_Parameter *param = new BP_Parameter(m_outputSlot);
    m_variableObject->getAsParameter(param);
    m_outputSlot->setParameterObject(param);
    m_outputSlot->setReference(variableObject->name());

    emit variableObjectChanged(m_variableObject);
}

void BP_VariableNode::setOutputSlot(BP_DataSlot *outputSlot)
{
    if (m_outputSlot == outputSlot)
        return;

    m_outputSlot = outputSlot;
    emit outputSlotChanged(m_outputSlot);
}


