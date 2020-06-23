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

#include <Graph/Slots/bp_flowslot.h>

#include <QPainter>

#include <Platform/bp_platformmanager.h>

BP_EventNode::BP_EventNode():BP_Node()
{

}

void BP_EventNode::addEventFlow(BP_FlowSlot *flow)
{
    eventFlows.insert(flow->flowName(),flow);
    calculateBounds();
}

BP_FlowSlot *BP_EventNode::getEventFlow(QString flowName)
{
    return eventFlows.value(flowName);
}

void BP_EventNode::createFlow(QString flowName)
{
    BP_FlowSlot *flowSlot = new BP_FlowSlot(this);
    flowSlot->setIsOutput(true);
    flowSlot->setShowFlowName(true);
    flowSlot->setFlowName(flowName);
    flowSlot->setParentNode(this);
    eventFlows.insert(flowName,flowSlot);
    calculateBounds();
}

void BP_EventNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::white);
    painter->setBrush(Qt::red);
    painter->drawRect(boundingRect());
    QPen titelPen = QPen(Qt::white,5);
    painter->setPen(titelPen);
    painter->drawText(7,13,m_eventName);
}

void BP_EventNode::calculateBounds()
{
    //initial flow + name
    int maxWidth = QFontMetrics(QFont()).boundingRect(m_eventName).width();
    int maxHeight = 30;

    //parameter bounds
    foreach (auto flowSlot, eventFlows.values()) {
        int slotWidth = flowSlot->boundingRect().width();
        maxWidth = maxWidth>slotWidth? maxWidth:slotWidth;
        maxHeight += 30;
    }
    maxWidth += 5;
    m_bounds.setHeight(maxHeight);
    m_bounds.setWidth(maxWidth);
    m_bounds.setX(0);
    m_bounds.setY(0);

    for (int i = 0; i < eventFlows.size(); ++i) {
        eventFlows.values().at(i)->setPos(maxWidth - eventFlows.values().at(i)->boundingRect().width(),30+30*i);
    }

}

QString BP_EventNode::renderNode(BP_PlatformManager *platform)
{
    return platform->renderEventNode(this);
}

BP_Node *BP_EventNode::nextNode()
{
    if(eventFlows.size()==0) return nullptr;
    return eventFlows.first()->connectedLinks().first()->outSlot()->parentNode();
}

QString BP_EventNode::getNodeTypeString()
{
    return "Event";
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
    calculateBounds();
    emit eventNameChanged(m_eventName);
}
