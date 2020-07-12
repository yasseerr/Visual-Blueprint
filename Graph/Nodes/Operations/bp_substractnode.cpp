
/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_substractnode.h"

#include <Graph/Slots/bp_dataslot.h>

#include <Platform/bp_platformmanager.h>

#include "Graph/bp_graphutils.h"

RegisterToolNodeType(BP_SubstractNode,"Add Operation")

BP_SubstractNode::BP_SubstractNode():BP_OperationToolNode()
{
    setDisplayText("-");
    addNewInput();
    addNewInput();
}

QString BP_SubstractNode::renderNode(BP_PlatformManager *platform)
{
    return platform->renderDefaultOperationTool(this,"substraction");
}

QString BP_SubstractNode::getNodeTypeString()
{
    return "Substraction";
}
