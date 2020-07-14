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

#include <QPainter>

QPen* BP_OperationToolNode::displayTextPen = new QPen(Qt::white,20);

BP_OperationToolNode::BP_OperationToolNode():BP_Node(),
    m_outputSlot(new BP_DataSlot(this)),
    m_maxNumberOfInputs(9999)
{
    m_outputSlot->setIsOutput(true);
    m_outputSlot->setShowName(false);
    m_outputSlot->setParentNode(this);
    m_outputSlot->setParentItem(this);

}

QVariant BP_OperationToolNode::toVariantBP()
{
    QVariantMap retMap = BP_Node::toVariantBP().toMap();
    retMap["type"] = getNodeTypeString();

    retMap["maxNumberOfInputs"] = m_maxNumberOfInputs;
    retMap["outputSlot"] = m_outputSlot->toVariantBP();
    retMap["displayText"] = m_displayText;

    QVariantList inputVariantList;
    foreach (auto input, m_inputSlots ) {
        inputVariantList << input->toVariantBP();
    }
    retMap["inputSlots"] = inputVariantList;
    return  retMap;

}

void BP_OperationToolNode::addNewInput()
{
    if(m_inputSlots.size() >= m_maxNumberOfInputs) return;
    BP_DataSlot *newSlot = new BP_DataSlot(this);
    newSlot->setIsOutput(false);
    newSlot->setShowName(true);
    newSlot->setParentNode(this);
    //newSlot->setReturnName();

    BP_Parameter *parameter = new  BP_Parameter(newSlot);
    parameter->setParameterName("_"+QString::number(m_inputSlots.size()));
    newSlot->setParameterObject(parameter);


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
    painter->setBrush(QColor(Qt::GlobalColor::gray));
    painter->drawRect(boundingRect());

//    painter->setOpacity(0.4);
//    painter->setBrush(Qt::blue);
//    painter->drawEllipse((boundingRect().center()+QPointF(5,-3)),10,10);
    painter->setPen(*displayTextPen);
    painter->setOpacity(1);
    painter->drawText(boundingRect().center()+QPointF(0,0),displayText());


}

void BP_OperationToolNode::calculateBounds()
{
    int minimumHeight = 30;
    int currentHeight = ((m_inputSlots.size()*30)>minimumHeight)?m_inputSlots.size()*30:minimumHeight;
    int currentWidth = 90;

    m_bounds  = QRectF(0,0,currentWidth,currentHeight);

    //setting the positions
    auto outputPosition = QPointF(70,(m_inputSlots.size()>0?-15:0)+
                                  currentHeight/(m_inputSlots.size()>0?m_inputSlots.size():0));
    m_outputSlot->setPos(outputPosition);

    for (int i = 0; i < m_inputSlots.size(); ++i) {
        auto inputSlot =  m_inputSlots.at(i);
        inputSlot->setPos(5,2+i*30);
    }

}

BP_Node *BP_OperationToolNode::nextNode()
{
    return  nullptr;
}

int BP_OperationToolNode::maxNumberOfInputs() const
{
    return m_maxNumberOfInputs;
}

QString BP_OperationToolNode::displayText() const
{
    return m_displayText;
}

QString BP_OperationToolNode::getNodeTypeString()
{
    return "Operation Tool";
}
