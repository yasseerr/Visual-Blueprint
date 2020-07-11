/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_operationtoolnode.h"

#include <Graph/Slots/bp_dataslot.h>

#include <Core/bp_parameter.h>

BP_OperationToolNode::BP_OperationToolNode():BP_Node(),
    m_outputSlot(new BP_DataSlot(this)),
    m_maxNumberOfInputs(9999)
{
    m_outputSlot->setIsOutput(true);
    m_outputSlot->setShowName(false);
    m_outputSlot->setParentNode(this);
    m_outputSlot->setParentItem(this);

}

void BP_OperationToolNode::addNewInput()
{
    if(m_inputSlots.size() >= m_maxNumberOfInputs) return;
    BP_DataSlot *newSlot = new BP_DataSlot(this);
    newSlot->setIsOutput(false);
    newSlot->setShowName(true);
    newSlot->setParentNode(this);
    newSlot->setReturnName(QString::number(m_inputSlots.size()));

    m_inputSlots << newSlot;
    calculateBounds();

}

QList<BP_DataSlot *> BP_OperationToolNode::inputSlots() const
{
    return m_inputSlots;
}

BP_DataSlot *BP_OperationToolNode::outputSlot() const
{
    return m_outputSlot;
}

void BP_OperationToolNode::setInputSlots(QList<BP_DataSlot *> inputSlots)
{
    m_inputSlots = inputSlots;
}

void BP_OperationToolNode::setOutputSlot(BP_DataSlot *outputSlot)
{
    if (m_outputSlot == outputSlot)
        return;

    m_outputSlot = outputSlot;
    emit outputSlotChanged(m_outputSlot);
}

void BP_OperationToolNode::setMaxNumberOfInputs(int maxNumberOfInputs)
{
    if (m_maxNumberOfInputs == maxNumberOfInputs)
        return;

    m_maxNumberOfInputs = maxNumberOfInputs;
    emit maxNumberOfInputsChanged(m_maxNumberOfInputs);
}

void BP_OperationToolNode::setDisplayText(QString displayText)
{
    if (m_displayText == displayText)
        return;

    m_displayText = displayText;
    emit displayTextChanged(m_displayText);
}

void BP_OperationToolNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    this->
}

void BP_OperationToolNode::calculateBounds()
{

}

BP_Node *BP_OperationToolNode::nextNode()
{
    return  this;
}

int BP_OperationToolNode::maxNumberOfInputs() const
{
    return m_maxNumberOfInputs;
}

QString BP_OperationToolNode::displayText() const
{
    return m_displayText;
}
