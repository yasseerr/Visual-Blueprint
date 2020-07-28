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

#pragma once
#include <Graph/bp_framebranch.h>
#include <Graph/bp_slot.h>

#include <QPainter>


BP_Link::BP_Link(QObject *parent):QObject(parent),QGraphicsItem(),m_inSlot(nullptr),m_outSlot(nullptr)
{
//    m_tempOutputPoint.setX(100);
//    m_tempOutputPoint.setY(-100);
}

QVariant BP_Link::toVariantBP()
{
    QVariantMap retMap ;
    retMap["inSlot"] = m_inSlot->slotID;
    retMap["outSlot"] = m_outSlot->slotID ;

    return retMap;

}

void BP_Link::fromVariant(QVariant var)
{

}

void BP_Link::disconnectSlot(BP_Slot *slot)
{
    if(slot == m_inSlot){
        setInSlot(nullptr);
    }
    else if(slot ==  m_outSlot){
        setOutSlot(nullptr);
    }

}

void BP_Link::disconnectAllSlots()
{
    if(m_inSlot){
        m_inSlot->removeLink(this);
        setInSlot(nullptr);
    }
    if(m_outSlot){
        m_outSlot->removeLink(this);
        setOutSlot(nullptr);
    }

}

BP_Slot *BP_Link::getTheOneConnectedSlot()
{
    if(m_inSlot && m_outSlot)
        return nullptr;
    else if(m_inSlot && !m_outSlot)
        return m_inSlot;
    else if (!m_inSlot && m_outSlot)
        return m_outSlot;

}

void BP_Link::drawCubicCurve(QPainter *painter, QPointF c1, QPointF c2,QPointF startPoint, QPointF endPoint)
{


    //seting up the linePen
    if(m_inSlot && m_inSlot->frameBranches().size()>0){
        int i =  0;
        foreach (auto branch, m_inSlot->frameBranches()) {
            painter->save();
            linePen.setWidth(2);
            //TODO use the colors from all the branches
            linePen.setColor(branch->branchColor());
            painter->setPen(linePen);
            auto deltaStart = startPoint+QPoint(0,2*i);
            auto deltaEnd = endPoint+QPoint(0,2*i);
            painter->translate(deltaStart);
            QPainterPath curvePath;
            curvePath.cubicTo(QPointF(50,2*i),deltaEnd-deltaStart+QPointF(-50,2*i),deltaEnd-deltaStart);
            painter->drawPath(curvePath);

            painter->restore();

            i++;
        }

    }else{
        painter->save();
        painter->translate(startPoint);
        QPainterPath curvePath;
        curvePath.cubicTo(QPointF(50,0),endPoint-startPoint+QPointF(-50,0),endPoint-startPoint);
        painter->drawPath(curvePath);

        painter->restore();
    }

}

QRectF BP_Link::boundingRect() const
{
    if(m_outSlot == nullptr && m_inSlot != nullptr)
        return  QRectF(m_inSlot->getAnchorPoint(),m_tempOutputPoint);
    else if(m_outSlot != nullptr && m_inSlot != nullptr)
        return  QRectF(m_inSlot->getAnchorPoint(),m_outSlot->getAnchorPoint());
    else
        return  QRectF(0,0,0,0);
}

void BP_Link::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    if(m_outSlot == nullptr && m_inSlot != nullptr)
        drawCubicCurve(painter,QPointF(),QPointF(),m_inSlot->getAnchorPoint(),m_tempOutputPoint);
        //painter->drawLine(m_inSlot->getAnchorPoint(),m_tempOutputPoint);
    else if(m_inSlot == nullptr && m_outSlot != nullptr)
        drawCubicCurve(painter,QPointF(),QPointF(),m_tempOutputPoint,m_outSlot->getAnchorPoint());
        //painter->drawLine(m_outSlot->getAnchorPoint(),m_tempOutputPoint);
    else if(m_outSlot != nullptr && m_inSlot != nullptr)
        drawCubicCurve(painter,QPointF(),QPointF(),m_inSlot->getAnchorPoint(),m_outSlot->getAnchorPoint());
        //painter->drawLine(m_inSlot->getAnchorPoint(),m_outSlot->getAnchorPoint());
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
    if(inSlot)m_inSlotPoint = m_inSlot->getAnchorPoint();

    emit inSlotChanged(m_inSlot);
}

void BP_Link::setOutSlot(BP_Slot *outSlot)
{
    if (m_outSlot == outSlot)
        return;

    m_outSlot = outSlot;
    if(outSlot)m_outSlotPoint = m_outSlot->getAnchorPoint();
    emit outSlotChanged(m_outSlot);
}

void BP_Link::setTempOutputPoint(QPointF tempOutputPoint)
{
    if (m_tempOutputPoint == tempOutputPoint)
        return;

    m_tempOutputPoint = tempOutputPoint;
    emit tempOutputPointChanged(m_tempOutputPoint);
}
