/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_asynctoolnode.h"

#include <Graph/Slots/bp_flowslot.h>

BP_AsyncToolNode::BP_AsyncToolNode():BP_Node(),
    m_flowInSlot(new BP_FlowSlot(this)),
    m_flowOutSlot(new BP_FlowSlot(this))

{
    setNoFlowNode(false);
    //the next node will be used later
    m_flowOutSlot->setIsOutput(true);
    m_flowOutSlot->setFlowName("out");
    m_flowOutSlot->setShowFlowName(false);
    m_flowOutSlot->setParentItem(this);
    m_flowOutSlot->setParentNode(this);

    m_flowInSlot->setIsOutput(false);
    m_flowInSlot->setShowFlowName(false);
    m_flowInSlot->setParentItem(this);
    m_flowInSlot->setParentNode(this);
}


BP_FlowSlot *BP_AsyncToolNode::flowInSlot() const
{
    return m_flowInSlot;
}

BP_FlowSlot *BP_AsyncToolNode::flowOutSlot() const
{
    return m_flowOutSlot;
}

QList<BP_FlowSlot *> BP_AsyncToolNode::asyncOutSlot() const
{
    return m_asyncOutSlots;
}

void BP_AsyncToolNode::setFlowInSlot(BP_FlowSlot *flowInSlot)
{
    if (m_flowInSlot == flowInSlot)
        return;

    m_flowInSlot = flowInSlot;
    emit flowInSlotChanged(m_flowInSlot);
}

void BP_AsyncToolNode::setFlowOutSlot(BP_FlowSlot *flowOutSlot)
{
    if (m_flowOutSlot == flowOutSlot)
        return;

    m_flowOutSlot = flowOutSlot;
    emit flowOutSlotChanged(m_flowOutSlot);
}

void BP_AsyncToolNode::setAsyncOutSlot(QList<BP_FlowSlot *> asyncOutSlots)
{
    if (m_asyncOutSlots == asyncOutSlots)
        return;

    m_asyncOutSlots = asyncOutSlots;
    emit asyncOutSlotChanged(m_asyncOutSlots);
}

void BP_AsyncToolNode::updateSlotsBranches(BP_Slot *slot)
{

}

BP_Node *BP_AsyncToolNode::nextNode()
{
    return nullptr;
}

void BP_AsyncToolNode::fromVariant(QVariant var)
{

}

QVariant BP_AsyncToolNode::toVariantBP()
{
    return "salam";
}
