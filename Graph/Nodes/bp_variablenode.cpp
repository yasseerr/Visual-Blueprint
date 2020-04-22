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

BP_VariableNode::BP_VariableNode(BP_Variable *variable):BP_Node(),m_variableObject(variable),m_outputSlot(new BP_DataSlot(this))
{
    m_outputSlot->setPos(0,0);
    m_outputSlot->setParentItem(this);
}

QRectF BP_VariableNode::boundingRect() const
{
    return  BP_Node::boundingRect();
}

void BP_VariableNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    BP_Node::paint(painter,option,widget);
}

BP_Variable *BP_VariableNode::variableObject() const
{
    return m_variableObject;
}

BP_DataSlot *BP_VariableNode::outputSlot() const
{
    return m_outputSlot;
}

void BP_VariableNode::setVariableObject(BP_Variable *variableObject)
{
    if (m_variableObject == variableObject)
        return;

    m_variableObject = variableObject;
    emit variableObjectChanged(m_variableObject);
}

void BP_VariableNode::setOutputSlot(BP_DataSlot *outputSlot)
{
    if (m_outputSlot == outputSlot)
        return;

    m_outputSlot = outputSlot;
    emit outputSlotChanged(m_outputSlot);
}


