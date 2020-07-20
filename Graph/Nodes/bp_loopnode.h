/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_LOOPNODE_H
#define BP_LOOPNODE_H

#include <QObject>

#include <Graph/bp_node.h>

class BP_FlowSlot;
class BP_DataSlot;
class BP_Parameter;
class BP_PlatformManager;

class BP_LoopNode : public BP_Node
{
    Q_OBJECT
    Q_CLASSINFO("name","loop")
    Q_PROPERTY(BP_FlowSlot* flowInSlot READ flowInSlot WRITE setFlowInSlot NOTIFY flowInSlotChanged)
    Q_PROPERTY(BP_FlowSlot* flowOutSlot READ flowOutSlot WRITE setFlowOutSlot NOTIFY flowOutSlotChanged)
    Q_PROPERTY(BP_FlowSlot* loopFlowSlot READ loopFlowSlot WRITE setLoopFlowSlot NOTIFY loopFlowSlotChanged)
    Q_PROPERTY(BP_DataSlot* startValueSlot READ startValueSlot WRITE setStartValueSlot NOTIFY startValueSlotChanged)
    Q_PROPERTY(BP_DataSlot* endValueSlot READ endValueSlot WRITE setEndValueSlot NOTIFY endValueSlotChanged)
    Q_PROPERTY(BP_DataSlot* stepSlot READ stepSlot WRITE setStepSlot NOTIFY stepSlotChanged)

    static int nodeTypeID;
    BP_FlowSlot* m_flowInSlot;

    BP_FlowSlot* m_flowOutSlot;

    BP_DataSlot* m_startValueSlot;

    BP_DataSlot* m_endValueSlot;

    BP_DataSlot* m_stepSlot;

    BP_FlowSlot* m_loopFlowSlot;

public:
    Q_INVOKABLE BP_LoopNode();

    virtual QVariant toVariantBP();
    virtual void fromVariant(QVariant var);

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // BP_Node interface
public:
    virtual void calculateBounds() override;
    virtual QString renderNode(BP_PlatformManager *platform) override;
    virtual BP_Node *nextNode() override;

    virtual QString getNodeTypeString() override;
    BP_FlowSlot* nextFlowSlot() const;
    virtual void mapInputFlowToOutput() override;

    BP_FlowSlot* flowInSlot() const;
    BP_FlowSlot* flowOutSlot() const;

    BP_DataSlot* startValueSlot() const;

    BP_DataSlot* endValueSlot() const;

    BP_DataSlot* stepSlot() const;

    BP_FlowSlot* loopFlowSlot() const;

public slots:
    void setFlowInSlot(BP_FlowSlot* flowInSlot);
    void setFlowOutSlot(BP_FlowSlot* flowOutSlot);

    void setStartValueSlot(BP_DataSlot* startValueSlot);

    void setEndValueSlot(BP_DataSlot* endValueSlot);

    void setStepSlot(BP_DataSlot* stepSlot);

    void setLoopFlowSlot(BP_FlowSlot* loopFlowSlot);

signals:
    void flowInSlotChanged(BP_FlowSlot* flowInSlot);
    void flowOutSlotChanged(BP_FlowSlot* flowOutSlot);
    void startValueSlotChanged(BP_DataSlot* startValueSlot);
    void endValueSlotChanged(BP_DataSlot* endValueSlot);
    void stepSlotChanged(BP_DataSlot* stepSlot);
    void loopFlowSlotChanged(BP_FlowSlot* loopFlowSlot);
};

#endif // BP_LOOPNODE_H
