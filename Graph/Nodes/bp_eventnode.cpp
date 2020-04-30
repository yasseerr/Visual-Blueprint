/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_eventnode.h"

#include <Graph/Links/bp_flowlink.h>

BP_EventNode::BP_EventNode():BP_Node()
{

}

void BP_EventNode::addEventFlow(BP_FlowSlot *flow)
{

}

BP_FlowSlot *BP_EventNode::getEventFlow(QString flowName)
{

}

void BP_EventNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{


}

void BP_EventNode::calculateBounds()
{

}

QString BP_EventNode::eventName() const
{
    return m_eventName;
}

void BP_EventNode::setEventName(QString eventName)
{
    if (m_eventName == eventName)
        return;

    m_eventName = eventName;
    emit eventNameChanged(m_eventName);
}
