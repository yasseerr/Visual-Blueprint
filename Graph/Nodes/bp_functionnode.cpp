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

#include <Graph/Slots/bp_dataslot.h>
#include <Graph/Slots/bp_flowslot.h>

#include <QPainter>

#include <Core/bp_function.h>
#include <Core/bp_parameter.h>

BP_FunctionNode::BP_FunctionNode(QObject *parent):BP_Node(parent)
{
    //adding the execution flow
    m_executionflowInSlot = new BP_FlowSlot(this);
    m_executionflowInSlot->setParentItem(this);
    m_executionflowInSlot->setPos(2,7);
    m_executionflowInSlot->setIsOutput(false);
    m_executionflowOutSlot = new BP_FlowSlot(this);
    m_executionflowOutSlot->setParentItem(this);
    m_executionflowOutSlot->setPos(2,7);
    m_executionflowInSlot->setIsOutput(true);
}

void BP_FunctionNode::loadCurrentFunction()
{
    //loading outputs
    //Check that there is a valid output
    m_returnSlot = new BP_DataSlot(this);
    m_returnSlot->setParameterObject(m_functionObject->returnArg());
    m_returnSlot->setIsOutput(true);

    //input args
    foreach (auto param, m_functionObject->inputArgs()) {
        BP_DataSlot *inputSlot = new BP_DataSlot(this);
        inputSlot->setParameterObject(param);
        m_inputParameters << inputSlot;

    }
    //check the positional args

    //add the keyWords

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

BP_Function *BP_FunctionNode::functionObject() const
{
    return m_functionObject;
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
    loadCurrentFunction();
    emit functionObjectChanged(m_functionObject);
}

void BP_FunctionNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Drawing the header
    painter->setBrush(Qt::darkBlue);
    painter->setPen(Qt::white);
    painter->drawRect(0,0,m_bounds.width(),30);
    painter->drawText(30,15,m_functionObject->name());

    //drawing the parameter section
    painter->setBrush(Qt::blue);
    //TODO put the name and the edit inside the slot item
    painter->drawRect(0,30,m_bounds.width(),m_bounds.height()-30);
    //parameters name
//    painter->drawText(0,40,"output");
//    for (int i = 0; i < m_inputParameters.size(); ++i) {
//        painter->drawText(30,50+i*20,m_inputParameters.at(i)->parameterObject()->parameterName());
//    }

}

void BP_FunctionNode::calculateBounds()
{
    //initial flow + name
    BP_Node::calculateBounds();
    int maxWidth = m_bounds.width() + 60;
    int maxHeight = 30;

    //output bound
    int outputWidth = 30 + QFontMetrics(QFont()).boundingRect("return").width();
    maxWidth = maxWidth>outputWidth? maxWidth:outputWidth;
    maxHeight += 30;
    //parameter bounds
    foreach (auto paramSlot, m_inputParameters) {
        int paramWidth = 30 + QFontMetrics(QFont()).boundingRect(paramSlot->parameterObject()->parameterName()).width();
        maxWidth = maxWidth>paramWidth? maxWidth:paramWidth;
        maxHeight += 30;
    }
    maxHeight += 10;
    m_bounds.setHeight(maxHeight);
    m_bounds.setWidth(maxWidth);
    m_bounds.setX(0);
    m_bounds.setY(0);
    //setting the child items position
    m_returnSlot->setPos(m_bounds.width()-m_returnSlot->boundingRect().width(),30);
    m_executionflowOutSlot->setPos(m_bounds.width()-15,7);
    for (int i = 0; i < m_inputParameters.size(); ++i) {
        m_inputParameters.at(i)->setPos(3,60+30*i);
    }

}
