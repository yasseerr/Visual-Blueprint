/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_flowslot.h"

#include <qpainter.h>

BP_FlowSlot::BP_FlowSlot(BP_Node *parent):BP_Slot(parent),m_showFlowName(false)
{
    trianglePolygone << QPoint(0,0) << QPoint(0,14) << QPoint(12,7);
}

bool BP_FlowSlot::acceptConnection(BP_Slot *secondSlot)
{
    if(!BP_Slot::acceptConnection(secondSlot)) return false;
    auto flowSlot = dynamic_cast<BP_FlowSlot*>(secondSlot);
    if(!flowSlot) return false;
    if(isOutput() == flowSlot->isOutput())return false;
    return true;
}

void BP_FlowSlot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::white);
    painter->drawText(0,4,flowName());
    painter->setBrush(Qt::white);
    painter->drawPolygon(trianglePolygone);
}

QRectF BP_FlowSlot::boundingRect() const
{
    return QRectF(0,0,15+flowNameWidth,15);
}

QPointF BP_FlowSlot::getAnchorPoint()
{
    return scenePos() + QPointF(7+flowNameWidth,7);
}

bool BP_FlowSlot::isOutput() const
{
    return m_isOutput;
}

QString BP_FlowSlot::flowName() const
{
    return m_flowName;
}

bool BP_FlowSlot::showFlowName() const
{
    return m_showFlowName;
}

void BP_FlowSlot::setIsOutput(bool isOutput)
{
    if (m_isOutput == isOutput)
        return;

    m_isOutput = isOutput;
    emit isOutputChanged(m_isOutput);
}

void BP_FlowSlot::setFlowName(QString flowName)
{
    if (m_flowName == flowName)
        return;

    m_flowName = flowName;

    flowNameWidth = QFontMetrics(QFont()).boundingRect(this->flowName()).width();
    trianglePolygone.translate(flowNameWidth,0);

    emit flowNameChanged(m_flowName);
}

void BP_FlowSlot::setShowFlowName(bool showFlowName)
{
    if (m_showFlowName == showFlowName)
        return;

    m_showFlowName = showFlowName;
    emit showFlowNameChanged(m_showFlowName);
}
