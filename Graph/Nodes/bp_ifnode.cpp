/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_ifnode.h"

#include <Graph/bp_graphutils.h>

#include <Graph/Slots/bp_dataslot.h>
#include <Graph/Slots/bp_flowslot.h>

#include <Core/bp_parameter.h>


RegisterToolNodeType(BP_IFNode,"Logic")

BP_IFNode::BP_IFNode():BP_LogicalNode(),
    m_falseFlowSlot(new BP_FlowSlot()),
    m_trueFlowSlot(new BP_FlowSlot()),
    m_flowInSlot(new BP_FlowSlot()),
    m_booleanSlot(new BP_DataSlot()),
    m_booleanParameter(new BP_Parameter())
{
    m_trueFlowSlot->setIsOutput(true);
    m_trueFlowSlot->setFlowName("false");
    m_trueFlowSlot->setShowFlowName(true);

    m_falseFlowSlot->setIsOutput(true);
    m_falseFlowSlot->setFlowName("false");
    m_falseFlowSlot->setShowFlowName(true);

    m_flowInSlot->setIsOutput(false);
    m_flowInSlot->setShowFlowName(false);

    m_booleanParameter->setParameterName("condition");

    m_booleanSlot->setShowName(true);
    m_booleanSlot->setParameterObject(m_booleanParameter);
    m_booleanSlot->setIsOutput(false);

}

BP_FlowSlot *BP_IFNode::trueFlowSlot() const
{
    return m_trueFlowSlot;
}

BP_FlowSlot *BP_IFNode::falseFlowSlot() const
{
    return m_falseFlowSlot;
}

BP_FlowSlot *BP_IFNode::flowInSlot() const
{
    return m_flowInSlot;
}

BP_DataSlot *BP_IFNode::booleanSlot() const
{
    return m_booleanSlot;
}

void BP_IFNode::setTrueFlowSlot(BP_FlowSlot *trueFlowSlot)
{
    if (m_trueFlowSlot == trueFlowSlot)
        return;

    m_trueFlowSlot = trueFlowSlot;
    emit trueFlowSlotChanged(m_trueFlowSlot);
}

void BP_IFNode::setFalseFlowSlot(BP_FlowSlot *falseFlowSlot)
{
    if (m_falseFlowSlot == falseFlowSlot)
        return;

    m_falseFlowSlot = falseFlowSlot;
    emit falseFlowSlotChanged(m_falseFlowSlot);
}

void BP_IFNode::setFlowInSlot(BP_FlowSlot *flowInSlot)
{
    if (m_flowInSlot == flowInSlot)
        return;

    m_flowInSlot = flowInSlot;
    emit flowInSlotChanged(m_flowInSlot);
}

void BP_IFNode::setBooleanSlot(BP_DataSlot *booleanSlot)
{
    if (m_booleanSlot == booleanSlot)
        return;

    m_booleanSlot = booleanSlot;
    emit booleanSlotChanged(m_booleanSlot);
}
