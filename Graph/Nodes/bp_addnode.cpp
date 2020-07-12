/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_addnode.h"

#include <Graph/Slots/bp_dataslot.h>

#include <Platform/bp_platformmanager.h>

#include "Graph/bp_graphutils.h"

RegisterToolNodeType(BP_AddNode,"Add Operation")

BP_AddNode::BP_AddNode():BP_OperationToolNode()
{
    setDisplayText("+");
    addNewInput();
    addNewInput();
}

QString BP_AddNode::renderNode(BP_PlatformManager *platform)
{
    return platform->renderDefaultOperationTool(this,"addition");
}

QString BP_AddNode::getNodeTypeString()
{
    return "Addition";
}
