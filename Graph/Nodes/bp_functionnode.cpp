/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_functionnode.h"

#include <Graph/Slots/bp_flowslot.h>

BP_FunctionNode::BP_FunctionNode(QObject *parent):BP_Node(parent)
{
    //adding the execution flow
    m_executionflowInSlot = new BP_FlowSlot(this);
    m_executionflowInSlot->setParentItem(this);
    m_executionflowInSlot->setPos(0,15);
    m_executionflowOutSlot = new BP_FlowSlot(this);
    m_executionflowOutSlot->setParentItem(this);
    m_executionflowOutSlot->setPos(100,15);

}

BP_FlowSlot *BP_FunctionNode::executionflowInSlot() const
{
    return m_executionflowInSlot;
}

BP_FlowSlot *BP_FunctionNode::executionflowOutSlot() const
{
    return m_executionflowOutSlot;
}

QList<BP_DataSlot *> BP_FunctionNode::inputParameters() const
{
    return m_inputParameters;
}

BP_DataSlot *BP_FunctionNode::returnSlot() const
{
    return m_returnSlot;
}

void BP_FunctionNode::setExecutionflowInSlot(BP_FlowSlot *executionflowInSlot)
{
    if (m_executionflowInSlot == executionflowInSlot)
        return;

    m_executionflowInSlot = executionflowInSlot;
    emit executionflowInSlotChanged(m_executionflowInSlot);
}

void BP_FunctionNode::setExecutionflowOutSlot(BP_FlowSlot *executionflowOutSlot)
{
    if (m_executionflowOutSlot == executionflowOutSlot)
        return;

    m_executionflowOutSlot = executionflowOutSlot;
    emit executionflowOutSlotChanged(m_executionflowOutSlot);
}

void BP_FunctionNode::setInputParameters(QList<BP_DataSlot *> inputParameters)
{
    if (m_inputParameters == inputParameters)
        return;

    m_inputParameters = inputParameters;
    emit inputParametersChanged(m_inputParameters);
}

void BP_FunctionNode::setReturnSlot(BP_DataSlot *returnSlot)
{
    if (m_returnSlot == returnSlot)
        return;

    m_returnSlot = returnSlot;
    emit returnSlotChanged(m_returnSlot);
}

void BP_FunctionNode::setFunctionObject(BP_Function *functionObject)
{
    if (m_functionObject == functionObject)
        return;

    m_functionObject = functionObject;
    emit functionObjectChanged(m_functionObject);
}

void BP_FunctionNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Drawing the header

    //drawing the parameter section

}

void BP_FunctionNode::calculateBounds()
{
    //initial flow + name
    BP_Node::calculateBounds();
    int maxWidth = m_bounds.width() + 60;
    int maxHeight = 60;

    //output bound

    //parameter bounds

    m_bounds.setHeight(maxHeight);
    m_bounds.setWidth(maxWidth);
    //setting the child items position
    m_executionflowOutSlot->setPos(m_bounds.width()-30,15);

}
