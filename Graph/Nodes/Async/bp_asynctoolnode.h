/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef ASYNCTOOLNODE_H
#define ASYNCTOOLNODE_H

#include <QObject>

#include <Graph/bp_node.h>

class BP_FlowSlot;

class BP_AsyncToolNode : public BP_Node
{
    Q_OBJECT

    Q_CLASSINFO("name","AsyncTool")

    Q_PROPERTY(BP_FlowSlot* flowInSlot READ flowInSlot WRITE setFlowInSlot NOTIFY flowInSlotChanged)
    Q_PROPERTY(BP_FlowSlot* flowOutSlot READ flowOutSlot WRITE setFlowOutSlot NOTIFY flowOutSlotChanged)
    Q_PROPERTY(QList<BP_FlowSlot*> asyncOutSlots READ asyncOutSlot WRITE setAsyncOutSlot NOTIFY asyncOutSlotChanged)

    BP_FlowSlot* m_flowInSlot;

    BP_FlowSlot* m_flowOutSlot;

    QList<BP_FlowSlot *> m_asyncOutSlots;

public:
    BP_AsyncToolNode();
    BP_FlowSlot* flowInSlot() const;
    BP_FlowSlot* flowOutSlot() const;

    QList<BP_FlowSlot*> asyncOutSlot() const;

public slots:
    void setFlowInSlot(BP_FlowSlot* flowInSlot);
    void setFlowOutSlot(BP_FlowSlot* flowOutSlot);

    void setAsyncOutSlot(QList<BP_FlowSlot*> asyncOutSlots);

signals:
    void flowInSlotChanged(BP_FlowSlot* flowInSlot);
    void flowOutSlotChanged(BP_FlowSlot* flowOutSlot);
    void asyncOutSlotChanged(QList<BP_FlowSlot*> asyncOutSlots);

    // BP_Node interface
public:
    void updateSlotsBranches(BP_Slot *slot) override;
    virtual BP_Node *nextNode() override;
    void fromVariant(QVariant var) override;
    QVariant toVariantBP() override;
};

#endif // ASYNCTOOLNODE_H
