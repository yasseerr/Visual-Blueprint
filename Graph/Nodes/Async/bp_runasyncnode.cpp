/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_runasyncnode.h"

#include <Graph/Slots/bp_flowslot.h>

#include <Graph/bp_framebranch.h>

#include <QPainter>
#include <bp_utils.h>
#include <Graph/bp_graphutils.h>

RegisterToolNodeType(BP_RunAsyncNode,"Async")

BP_RunAsyncNode::BP_RunAsyncNode()
{
    BP_FlowSlot *newAsync1Slot  = new BP_FlowSlot(this);
    newAsync1Slot->setIsOutput(true);
    newAsync1Slot->setFlowName("Async One");
    newAsync1Slot->setShowFlowName(true);
    newAsync1Slot->setParentItem(this);
    newAsync1Slot->setParentNode(this);

    m_asyncOutSlots << newAsync1Slot;

    BP_FrameBranch *newBranch = new BP_FrameBranch(newAsync1Slot);
    newBranch->setSplitNode(this);
    m_subBranches << newBranch;
    newAsync1Slot->m_frameBranches << newBranch;

    //using the same branches as the original ones
    QSet<BP_Thread*> originalThreads;
    getOriginalThreads(originalThreads);

    newBranch->m_threads.unite(originalThreads);

    calculateBounds();
}

void BP_RunAsyncNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QColor(Qt::GlobalColor::gray));
    painter->drawRect(boundingRect());

    painter->setPen(Qt::white);
    painter->setOpacity(0.8);
    painter->drawText(QPoint(boundingRect().center().x()-TextHalfWidth("Run Async"),15),"Run Async");
}

void BP_RunAsyncNode::calculateBounds()
{
    BP_Node::calculateBounds();
    int maxWidth = 0;
    int maxHeight = 60;
    //output bound
    int outputWidth =30+ m_flowInSlot->boundingRect().width()*2 + QFontMetrics(QFont()).boundingRect("Run Async").width();
    maxWidth = maxWidth>outputWidth? maxWidth:outputWidth;


    //TODO loop around the new threads slots in the looop
    auto firstSlot = m_asyncOutSlots.first();
    maxWidth = firstSlot->boundingRect().width()>maxWidth?firstSlot->boundingRect().width():maxWidth;

    m_bounds.setHeight(maxHeight);
    m_bounds.setWidth(maxWidth);
    m_bounds.setX(0);
    m_bounds.setY(0);
    //setting the child items position
    firstSlot->setPos(m_bounds.width()-firstSlot->boundingRect().width(),40);

    m_flowOutSlot->setPos(5+m_bounds.width()-m_flowOutSlot->boundingRect().width(),7);
    m_flowInSlot->setPos(5,7);

}

QString BP_RunAsyncNode::renderNode(BP_PlatformManager *platform)
{
    CHECK_FIRST_REFERENCE
    return platform->renderRunAsyncNode(this);
}

QString BP_RunAsyncNode::getNodeTypeString()
{
    return "Run Async";
}
