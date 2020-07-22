/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_createthreadsnode.h"
#include <Graph/bp_graphutils.h>
#include <Graph/Slots/bp_dataslot.h>
#include <Graph/Slots/bp_flowslot.h>
#include <Core/bp_parameter.h>
#include <QPainter>
#include <Graph/Links/bp_link.h>
#include <Platform/bp_platformmanager.h>


RegisterToolNodeType(BP_CreateThreadsNode,"Threading")

BP_CreateThreadsNode::BP_CreateThreadsNode()
{
    BP_FlowSlot *newThread1Slot  = new BP_FlowSlot(this);
    newThread1Slot->setIsOutput(true);
    newThread1Slot->setFlowName("Thread One");
    newThread1Slot->setShowFlowName(true);
    newThread1Slot->setParentItem(this);
    newThread1Slot->setParentNode(this);

    m_subThreadsSlots << newThread1Slot;

    calculateBounds();
}


void BP_CreateThreadsNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QColor(Qt::GlobalColor::gray));
    painter->drawRect(boundingRect());

    painter->setPen(Qt::white);
    painter->setOpacity(0.8);
    painter->drawText(QPoint(boundingRect().center().x()-TextHalfWidth("Create Threads"),15),"Create Threads");
}

void BP_CreateThreadsNode::calculateBounds()
{
    BP_Node::calculateBounds();
    int maxWidth = 0;
    int maxHeight = 60;

    //output bound
    int outputWidth =30+ m_flowInSlot->boundingRect().width()*2 + QFontMetrics(QFont()).boundingRect("Create Threads").width();
    maxWidth = maxWidth>outputWidth? maxWidth:outputWidth;


    //TODO loop around the new threads slots in the looop
    auto firstThreadSlot = m_subThreadsSlots.first();
    maxWidth = firstThreadSlot->boundingRect().width()>maxWidth?firstThreadSlot->boundingRect().width():maxWidth;

    m_bounds.setHeight(maxHeight);
    m_bounds.setWidth(maxWidth);
    m_bounds.setX(0);
    m_bounds.setY(0);
    //setting the child items position
    firstThreadSlot->setPos(m_bounds.width()-firstThreadSlot->boundingRect().width(),40);

    m_flowOutSlot->setPos(5+m_bounds.width()-m_flowOutSlot->boundingRect().width(),7);
    m_flowInSlot->setPos(5,7);
}

QString BP_CreateThreadsNode::renderNode(BP_PlatformManager *platform)
{
    CHECK_FIRST_REFERENCE
    return platform->renderCreateThreadsNode(this);
}

QString BP_CreateThreadsNode::getNodeTypeString()
{
    return "Create Thread";
}

QVariant BP_CreateThreadsNode::toVariantBP()
{
    return 1;
}

void BP_CreateThreadsNode::fromVariant(QVariant var)
{

}
