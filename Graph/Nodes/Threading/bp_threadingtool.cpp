/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_threadingtool.h"

#include <Graph/Slots/bp_flowslot.h>

#include <Graph/Links/bp_link.h>



BP_ThreadingTool::BP_ThreadingTool():BP_Node(),
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

BP_FlowSlot *BP_ThreadingTool::flowInSlot() const
{
    return m_flowInSlot;
}

BP_FlowSlot *BP_ThreadingTool::flowOutSlot() const
{
    return m_flowOutSlot;
}

QList<BP_FlowSlot *> BP_ThreadingTool::subThreadsSlots() const
{
    return m_subThreadsSlots;
}

void BP_ThreadingTool::setFlowInSlot(BP_FlowSlot *flowInSlot)
{
    if (m_flowInSlot == flowInSlot)
        return;
    
    m_flowInSlot = flowInSlot;
    emit flowInSlotChanged(m_flowInSlot);
}

void BP_ThreadingTool::setFlowOutSlot(BP_FlowSlot *flowOutSlot)
{
    if (m_flowOutSlot == flowOutSlot)
        return;

    m_flowOutSlot = flowOutSlot;
    emit flowOutSlotChanged(m_flowOutSlot);
}

void BP_ThreadingTool::setSubThreadsSlots(QList<BP_FlowSlot *> subThreadsSlots)
{
    if (m_subThreadsSlots == subThreadsSlots)
        return;

    m_subThreadsSlots = subThreadsSlots;
    emit subThreadsSlotsChanged(m_subThreadsSlots);
}

BP_Node *BP_ThreadingTool::nextNode()
{
    if(m_flowOutSlot->connectedLinks().size()==0) return nullptr;
    return m_flowOutSlot->connectedLinks().first()->outSlot()->parentNode();
}

void BP_ThreadingTool::updateSlotsBranches(BP_Slot *slot){

    if(!slot || slot == m_flowInSlot){
        auto joinedList = m_flowInSlot->getJoinedBranches();
        m_flowOutSlot->setFrameBranches(joinedList);
        setOriginalBranches(joinedList);
        m_flowOutSlot->notifyConnectedNodes();
        if(m_clotureNode)m_clotureNode->updateSlotsBranches(nullptr);
    }

}


void BP_ThreadingTool::fromVariant(QVariant var)
{
    BP_Node::fromVariant(var);
    auto varMap = var.toMap();
    
    m_flowInSlot->fromVariant(varMap["flowInSlot"]);
    m_flowOutSlot->fromVariant(varMap["flowOutSlot"]);
    auto subThreadsVariantList = varMap["subThreadsSlots"].toList();
    for (int i = 0; i < m_subThreadsSlots.size(); ++i) {
        m_subThreadsSlots[i]->fromVariant(subThreadsVariantList[i]);
    }

}

QVariant BP_ThreadingTool::toVariantBP()
{
    QVariantMap retMap = BP_Node::toVariantBP().toMap();
    retMap["type"] = getNodeTypeString();

    retMap["flowInSlot"] = m_flowInSlot->toVariantBP();
    retMap["flowOutSlot"] = m_flowOutSlot->toVariantBP();
    QVariantList subThreadsVar;
    foreach (auto threadSlot, m_subThreadsSlots) {
        subThreadsVar << threadSlot->toVariantBP();
    }
    retMap["subThreadsSlots"] = subThreadsVar;

    return retMap;
}
