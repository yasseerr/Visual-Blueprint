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

#include <Graph/bp_framebranch.h>
#include <Graph/bp_graphutils.h>

#include <Graph/Slots/bp_dataslot.h>
#include <Graph/Slots/bp_flowslot.h>

#include <Core/bp_parameter.h>

#include <QPainter>

#include <Graph/Links/bp_link.h>

#include <Platform/bp_platformmanager.h>


RegisterToolNodeType(BP_IFNode,"Programing")

BP_IFNode::BP_IFNode():BP_LogicalNode(),
    m_falseFlowSlot(new BP_FlowSlot()),
    m_trueFlowSlot(new BP_FlowSlot()),
    m_nextFlowSlot(new BP_FlowSlot()),
    m_flowInSlot(new BP_FlowSlot()),
    m_booleanSlot(new BP_DataSlot()),
    m_booleanParameter(new BP_Parameter())
{
    setNoFlowNode(false);
    m_trueFlowSlot->setIsOutput(true);
    m_trueFlowSlot->setFlowName("true");
    m_trueFlowSlot->setShowFlowName(true);
    m_trueFlowSlot->setParentItem(this);
    m_trueFlowSlot->setParentNode(this);
    BP_FrameBranch *trueFrameBranch = new BP_FrameBranch(m_trueFlowSlot);
    m_subBranches << trueFrameBranch;
    trueFrameBranch->setSplitNode(this);
    m_trueFlowSlot->m_frameBranches << trueFrameBranch;

    m_falseFlowSlot->setIsOutput(true);
    m_falseFlowSlot->setFlowName("false");
    m_falseFlowSlot->setShowFlowName(true);
    m_falseFlowSlot->setParentItem(this);
    m_falseFlowSlot->setParentNode(this);
    BP_FrameBranch *falseFrameBranch = new BP_FrameBranch(m_falseFlowSlot);
    m_subBranches << falseFrameBranch;
    falseFrameBranch->setSplitNode(this);
    m_falseFlowSlot->m_frameBranches << falseFrameBranch;

    //the next node will be used later
    m_nextFlowSlot->setIsOutput(true);
    m_nextFlowSlot->setFlowName("next");
    m_nextFlowSlot->setShowFlowName(true);
    m_nextFlowSlot->setParentItem(this);
    m_nextFlowSlot->setParentNode(this);

    m_flowInSlot->setIsOutput(false);
    m_flowInSlot->setShowFlowName(false);
    m_flowInSlot->setParentItem(this);
    m_flowInSlot->setParentNode(this);

    m_booleanParameter->setParameterName("condition");
    m_booleanParameter->setIsImported(false);

    m_booleanSlot->setShowName(true);
    m_booleanSlot->setParameterObject(m_booleanParameter);
    m_booleanSlot->setIsOutput(false);
    m_booleanSlot->setParentItem(this);
    this->calculateBounds();


}

QVariant BP_IFNode::toVariantBP()
{
    QVariantMap retMap = BP_Node::toVariantBP().toMap();
    retMap["type"] = getNodeTypeString();

    retMap["trueFlowSlot"] = m_trueFlowSlot->toVariantBP();
    retMap["falseFlowSlot"] = m_falseFlowSlot->toVariantBP();
    retMap["flowInSlot"] = m_flowInSlot->toVariantBP();
    retMap["booleanSlot"] = m_booleanSlot->toVariantBP();
    retMap["booleanParameter"] = m_booleanParameter->toVariantBP();
    return  retMap;
}

void BP_IFNode::fromVariant(QVariant var)
{
    BP_Node::fromVariant(var);
    auto varMap = var.toMap();
    m_trueFlowSlot->fromVariant(varMap["trueFlowSlot"]);
    m_falseFlowSlot->fromVariant(varMap["falseFlowSlot"]);
    m_flowInSlot->fromVariant(varMap["flowInSlot"]);
    m_booleanSlot->fromVariant(varMap["booleanSlot"]);
    //m_booleanParameter->fromVariant(varMap["flowInSlot"]);
    //TODO study the need of saving the boolean parameter
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

BP_Parameter *BP_IFNode::booleanParameter() const
{
    return m_booleanParameter;
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

void BP_IFNode::setBooleanParameter(BP_Parameter *booleanParameter)
{
    if (m_booleanParameter == booleanParameter)
        return;

    m_booleanParameter = booleanParameter;
    emit booleanParameterChanged(m_booleanParameter);
}

void BP_IFNode::setNextFlowSlot(BP_FlowSlot *nextFlowSlot)
{
    if (m_nextFlowSlot == nextFlowSlot)
        return;

    m_nextFlowSlot = nextFlowSlot;
    emit nextFlowSlotChanged(m_nextFlowSlot);
}

void BP_IFNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QColor(Qt::GlobalColor::gray));
    painter->drawRect(boundingRect());

    painter->setPen(Qt::white);
    painter->setOpacity(0.8);
    painter->drawText(boundingRect().center().x(),15,"IF");
}

void BP_IFNode::calculateBounds()
{
    //initial flow + name
    BP_Node::calculateBounds();

    m_bounds.setHeight(100);
    m_bounds.setWidth(10+qMax(m_flowInSlot->boundingRect().width()+m_trueFlowSlot->boundingRect().width(),
                           m_booleanSlot->boundingRect().width()+ m_falseFlowSlot->boundingRect().width()));
    m_flowInSlot->setPos(5,10);
    m_booleanSlot->setPos(5,40);
    m_trueFlowSlot->setPos(m_booleanSlot->boundingRect().width()+10,10);
    m_falseFlowSlot->setPos(m_booleanSlot->boundingRect().width()+10,45);
    m_nextFlowSlot->setPos(m_booleanSlot->boundingRect().width()+10,80);
}

QString BP_IFNode::renderNode(BP_PlatformManager *platform)
{
    return platform->renderIFStatement(this);
}

BP_Node *BP_IFNode::nextNode()
{
//    if(m_nextFlowSlot->connectedLinks().size()==0) return nullptr;
//    return m_nextFlowSlot->connectedLinks().first()->outSlot()->parentNode();
    return clotureNode();
    //return BP_GraphUtils::getInstance()->getEndOfBranchForNode(this);
}

void BP_IFNode::updateSlotsBranches(BP_Slot *slot)
{
    if(slot == m_flowInSlot){
        m_originalBranches.clear();
        m_originalBranches << m_flowInSlot->getJoinedBranches();
        //TODO update the cloture node
        if(m_clotureNode)m_clotureNode->updateSlotsBranches(nullptr);

        m_booleanSlot->setFrameBranches(m_originalBranches);
        m_booleanSlot->notifyConnectedNodes();
    }
}

QString BP_IFNode::getNodeTypeString()
{
    return "If statemenet";
}

BP_FlowSlot *BP_IFNode::nextFlowSlot() const
{
    return m_nextFlowSlot;
}

void BP_IFNode::mapInputFlowToOutput()
{
    auto theNodeBranches = BP_GraphUtils::getInstance()->getReplacedSubBranchesWithParents(m_flowInSlot);
    BP_GraphUtils::getInstance()->setNodeParentBranches(this,theNodeBranches);
    //create node sube branches and save them
    int trueBranch = BP_GraphUtils::getInstance()->getNewBranchID(this);
    int falseBranch = BP_GraphUtils::getInstance()->getNewBranchID(this);
    //add the branches to the trueSlot
    m_trueFlowSlot->addBranch(trueBranch);
    //add the branches to the falseSlot
    m_falseFlowSlot->addBranch(falseBranch);
    //BP_GraphUtils::getNewBranchID(this);
}
