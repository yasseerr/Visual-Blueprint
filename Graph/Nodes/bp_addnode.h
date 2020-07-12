/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_ADDNODE_H
#define BP_ADDNODE_H

#include "bp_operationtoolnode.h"

#include <QObject>

#include <Graph/bp_node.h>

class BP_AddNode : public BP_OperationToolNode
{
    Q_OBJECT
    Q_CLASSINFO("name","Addition")
public:
    Q_INVOKABLE BP_AddNode();

    static int nodeTypeID ;

    // BP_Node interface
public:
    virtual QString renderNode(BP_PlatformManager *platform) override;
    QString getNodeTypeString() override;
};

#endif // BP_ADDNODE_H
