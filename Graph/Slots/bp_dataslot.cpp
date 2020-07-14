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

BP_DataSlot::BP_DataSlot(BP_Node *parent):BP_Slot(parent),m_parameterObject(nullptr),m_parameterWidth(50),
    m_showName(true),m_returnName("return")
{
    setIsOutput(false);
    setTextColor(Qt::yellow);
    setParentNode(parent);

}

QVariant BP_DataSlot::toVariantBP()
{
    QVariantMap retMap = BP_Slot::toVariantBP().toMap() ;
    retMap["type"] = "data" ;
    retMap["parameterObject"] = m_parameterObject?m_parameterObject->toVariantBP():false;
    retMap["showName"] = m_showName;
    retMap["returnName"] = m_returnName;

    return retMap;
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


void BP_DataSlot::setShowName(bool showName)
{
    if (m_showName == showName)
        return;

    m_showName = showName;
    emit showNameChanged(m_showName);
}

QRectF BP_DataSlot::boundingRect() const
{
    return  QRectF(0,0,20+m_parameterWidth,20);
}

void BP_DataSlot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(textColor());
    painter->setBrush(Qt::white);
    if(isOutput()){
        if(m_showName){
            painter->drawText(0,15,returnName());
            painter->drawEllipse(QRectF(m_parameterWidth,3,16,16));
        }else {
            painter->drawEllipse(QRectF(0,3,16,16));
        }
    }else {
        //TODO add m_showName constraint when its an input
        if(m_parameterObject)
            painter->drawText(20,15,m_parameterObject->parameterName());
        else
            painter->drawText(20,15,"self");
        painter->drawEllipse(QRectF(0,3,16,16));
    }
}

QPointF BP_DataSlot::getAnchorPoint()
{
    QPoint offset;
    if(isOutput() && m_showName){
        offset.setX(m_parameterWidth+8);
        offset.setY(3+8);
    }
    else if(isOutput() && !m_showName){
        offset.setX(8);
        offset.setY(3+8);
    }
    else {
        offset.setX(8);
        offset.setY(3+8);
    }
    return this->scenePos() + offset;
}

bool BP_DataSlot::acceptConnection(BP_Slot *secondSlot)
{
    if(!BP_Slot::acceptConnection(secondSlot)) return false;
    auto dataSlot = dynamic_cast<BP_DataSlot*>(secondSlot);
    if(!dataSlot) return false;
    else if(dataSlot->isOutput() == this->isOutput()) return false;
    //TODO check the type
    return true;
}

void BP_DataSlot::showNextNodeOptions()
{

}

bool BP_DataSlot::showName() const
{
    return m_showName;
}

