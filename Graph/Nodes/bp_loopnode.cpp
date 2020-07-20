/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_loopnode.h"

RegisterToolNodeType(BP_LoopNode,"Programing")
BP_LoopNode::BP_LoopNode()
{

}

QVariant BP_LoopNode::toVariantBP()
{
    return 1;
}

void BP_LoopNode::fromVariant(QVariant var)
{

}

void BP_LoopNode::calculateBounds()
{

}

QString BP_LoopNode::renderNode(BP_PlatformManager *platform)
{
    return "";
}

BP_Node *BP_LoopNode::nextNode()
{
    return nullptr;
}

QString BP_LoopNode::getNodeTypeString()
{
    return "";
}

BP_FlowSlot *BP_LoopNode::nextFlowSlot() const
{
    return nullptr;
}

void BP_LoopNode::mapInputFlowToOutput()
{
    return "Loop";
}
