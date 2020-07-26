/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_THREADINGTOOL_H
#define BP_THREADINGTOOL_H

#include <QObject>

#include <Graph/bp_node.h>

class BP_FlowSlot;

class BP_ThreadingTool : public BP_Node
{
    Q_OBJECT
    Q_CLASSINFO("name","ThreadingTool")

    Q_PROPERTY(BP_FlowSlot* flowInSlot READ flowInSlot WRITE setFlowInSlot NOTIFY flowInSlotChanged)
    Q_PROPERTY(BP_FlowSlot* flowOutSlot READ flowOutSlot WRITE setFlowOutSlot NOTIFY flowOutSlotChanged)
    Q_PROPERTY(QList<BP_FlowSlot*> subThreadsSlots READ subThreadsSlots WRITE setSubThreadsSlots NOTIFY subThreadsSlotsChanged)

protected:
    BP_FlowSlot* m_flowInSlot;

    BP_FlowSlot* m_flowOutSlot;

    QList<BP_FlowSlot*> m_subThreadsSlots;

public:
    BP_ThreadingTool();
    BP_FlowSlot* flowInSlot() const;
    BP_FlowSlot* flowOutSlot() const;

    QList<BP_FlowSlot*> subThreadsSlots() const;

public slots:
    void setFlowInSlot(BP_FlowSlot* flowInSlot);
    void setFlowOutSlot(BP_FlowSlot* flowOutSlot);

    void setSubThreadsSlots(QList<BP_FlowSlot*> subThreadsSlots);

signals:
    void flowInSlotChanged(BP_FlowSlot* flowInSlot);
    void flowOutSlotChanged(BP_FlowSlot* flowOutSlot);
    void subThreadsSlotsChanged(QList<BP_FlowSlot*> subThreadsSlots);

    // BP_Node interface
public:
    void updateSlotsBranches(BP_Slot *slot) override;
    virtual BP_Node *nextNode() override;
    void fromVariant(QVariant var) override;
    QVariant toVariantBP() override;
};

#endif // BP_THREADINGTOOL_H
