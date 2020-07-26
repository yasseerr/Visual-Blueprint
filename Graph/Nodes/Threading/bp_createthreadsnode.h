/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_CREATETHREADSNODE_H
#define BP_CREATETHREADSNODE_H

#include "bp_threadingtool.h"

#include <QObject>

class BP_CreateThreadsNode : public BP_ThreadingTool
{
    Q_OBJECT
    Q_CLASSINFO("name","Create Thread")

    static int nodeTypeID;

public:
    Q_INVOKABLE BP_CreateThreadsNode();

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // BP_Node interface
public:
    virtual void calculateBounds() override;
    virtual QString renderNode(BP_PlatformManager *platform) override;
    virtual QString getNodeTypeString() override;    

//    virtual QVariant toVariantBP() override;
//    virtual void fromVariant(QVariant var) override;
};

#endif // BP_CREATETHREADSNODE_H
