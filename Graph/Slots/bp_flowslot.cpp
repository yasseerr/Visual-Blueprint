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

BP_FlowSlot::BP_FlowSlot(BP_Node *parent):BP_Slot(parent)
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

    painter->setBrush(Qt::white);
    painter->drawPolygon(trianglePolygone);

}

bool BP_FlowSlot::isOutput() const
{
    return m_isOutput;
}

void BP_FlowSlot::setIsOutput(bool isOutput)
{
    if (m_isOutput == isOutput)
        return;

    m_isOutput = isOutput;
    emit isOutputChanged(m_isOutput);
}
