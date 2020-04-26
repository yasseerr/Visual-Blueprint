/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_link.h"

#include <Graph/bp_slot.h>

#include <QPainter>

BP_Link::BP_Link(QObject *parent):QObject(parent),QGraphicsItem(),m_inSlot(nullptr),m_outSlot(nullptr)
{

}

QRectF BP_Link::boundingRect() const
{
    if(m_outSlot == nullptr && m_inSlot == nullptr)
        return QRectF(0,0,0,0);
    else if(m_outSlot == nullptr && m_inSlot != nullptr)
        return  QRectF(m_inSlot->pos(),m_tempOutputPoint);
    else if(m_outSlot != nullptr && m_inSlot != nullptr)
        return  QRectF(m_inSlot->pos(),m_outSlot->pos());
}

void BP_Link::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    if(m_outSlot == nullptr && m_inSlot != nullptr)
        painter->drawLine(m_inSlot->pos(),m_tempOutputPoint);
    if(m_outSlot != nullptr && m_inSlot != nullptr)
        painter->drawLine(m_inSlot->pos(),m_outSlot->pos());
}

BP_Slot *BP_Link::inSlot() const
{
    return m_inSlot;
}

BP_Slot *BP_Link::outSlot() const
{
    return m_outSlot;
}

QPointF BP_Link::tempOutputPoint() const
{
    return m_tempOutputPoint;
}

void BP_Link::setInSlot(BP_Slot *inSlot)
{
    if (m_inSlot == inSlot)
        return;

    m_inSlot = inSlot;
    emit inSlotChanged(m_inSlot);
}

void BP_Link::setOutSlot(BP_Slot *outSlot)
{
    if (m_outSlot == outSlot)
        return;

    m_outSlot = outSlot;
    emit outSlotChanged(m_outSlot);
}

void BP_Link::setTempOutputPoint(QPointF tempOutputPoint)
{
    if (m_tempOutputPoint == tempOutputPoint)
        return;

    m_tempOutputPoint = tempOutputPoint;
    emit tempOutputPointChanged(m_tempOutputPoint);
}
