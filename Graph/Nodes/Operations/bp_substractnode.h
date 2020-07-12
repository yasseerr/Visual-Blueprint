/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_SUBSTRACTNODE_H
#define BP_SUBSTRACTNODE_H


#include <QObject>

#include <Graph/bp_node.h>

#include <Graph/Nodes/bp_operationtoolnode.h>

class BP_SubstractNode : public BP_OperationToolNode
{
    Q_OBJECT
    Q_CLASSINFO("name","Substraction")
public:
    Q_INVOKABLE BP_SubstractNode();

    static int nodeTypeID ;

    // BP_Node interface
public:
    virtual QString renderNode(BP_PlatformManager *platform) override;
    QString getNodeTypeString() override;
};

#endif // BP_SUBSTRACTNODE_H
