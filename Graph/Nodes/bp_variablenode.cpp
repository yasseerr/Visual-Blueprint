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

#include <Core/bp_variable.h>

BP_VariableNode::BP_VariableNode():BP_Node(),m_variableObject(nullptr),m_outputSlot(new BP_DataSlot(this))
{
    m_outputSlot->setParentItem(this);

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


