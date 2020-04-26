/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_dataslot.h"

#include <QFontMetrics>
#include <QPainter>

#include <Core/bp_parameter.h>

BP_DataSlot::BP_DataSlot(BP_Node *parent):BP_Slot(parent),m_parameterObject(nullptr),m_isOutput(false),m_parameterWidth(50)
{

}

BP_Parameter *BP_DataSlot::parameterObject() const
{
    return m_parameterObject;
}

void BP_DataSlot::setParameterObject(BP_Parameter *parameterObject)
{
    if (m_parameterObject == parameterObject)
        return;

    m_parameterObject = parameterObject;
    m_parameterWidth = QFontMetrics(QFont()).boundingRect(m_parameterObject->parameterName()).width();
    emit parameterObjectChanged(m_parameterObject);
}

void BP_DataSlot::setIsOutput(bool isOutput)
{
    if (m_isOutput == isOutput)
        return;

    m_isOutput = isOutput;
    emit isOutputChanged(m_isOutput);
}

QRectF BP_DataSlot::boundingRect() const
{
    return  QRectF(0,0,20+m_parameterWidth,20);
}

void BP_DataSlot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::yellow);
    painter->setBrush(Qt::white);
    if(isOutput()){
        painter->drawText(0,15,"return");
        painter->drawEllipse(QRectF(m_parameterWidth,3,16,16));
    }else {
        if(m_parameterObject)
            painter->drawText(20,15,m_parameterObject->parameterName());
        painter->drawEllipse(QRectF(0,3,16,16));
    }
}

QPointF BP_DataSlot::getAnchorPoint()
{
    QPoint offset;
    if(isOutput()){
        offset.setX(m_parameterWidth+8);
        offset.setY(3+8);
    }else {
        offset.setX(8);
        offset.setY(3+8);
    }
    return this->scenePos() + offset;
}

bool BP_DataSlot::isOutput() const
{

    return m_isOutput;
}
