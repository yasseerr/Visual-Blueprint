/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_RUNASYNCNODE_H
#define BP_RUNASYNCNODE_H

#include "bp_asynctoolnode.h"

#include <QObject>



class BP_RunAsyncNode : public BP_AsyncToolNode
{
    Q_OBJECT

    Q_CLASSINFO("name","Run Async")

    static int nodeTypeID;
public:
    Q_INVOKABLE BP_RunAsyncNode();



    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // BP_Node interface
    virtual void calculateBounds() override;
    virtual QString renderNode(BP_PlatformManager *platform) override;
    virtual QString getNodeTypeString() override;
};

#endif // BP_RUNASYNCNODE_H
