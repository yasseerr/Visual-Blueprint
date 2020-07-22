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



BP_ThreadingTool::BP_ThreadingTool()
{

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
