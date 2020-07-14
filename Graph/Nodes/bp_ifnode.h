/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_IFNODE_H
#define BP_IFNODE_H

#include "bp_logicalnode.h"


class BP_FlowSlot;
class BP_DataSlot;
class BP_Parameter;

class BP_IFNode : public BP_LogicalNode
{
    Q_OBJECT
    Q_CLASSINFO("name","if statment")
    Q_PROPERTY(BP_FlowSlot* trueFlowSlot READ trueFlowSlot WRITE setTrueFlowSlot NOTIFY trueFlowSlotChanged)
    Q_PROPERTY(BP_FlowSlot* falseFlowSlot READ falseFlowSlot WRITE setFalseFlowSlot NOTIFY falseFlowSlotChanged)
    Q_PROPERTY(BP_FlowSlot* nextFlowSlot READ nextFlowSlot WRITE setNextFlowSlot NOTIFY nextFlowSlotChanged)
    Q_PROPERTY(BP_FlowSlot* flowInSlot READ flowInSlot WRITE setFlowInSlot NOTIFY flowInSlotChanged)
    Q_PROPERTY(BP_DataSlot* booleanSlot READ booleanSlot WRITE setBooleanSlot NOTIFY booleanSlotChanged)
    Q_PROPERTY(BP_Parameter* booleanParameter READ booleanParameter WRITE setBooleanParameter NOTIFY booleanParameterChanged)

    BP_FlowSlot* m_trueFlowSlot;
    BP_FlowSlot* m_falseFlowSlot;
    BP_FlowSlot* m_flowInSlot;


    static int nodeTypeID;

    BP_DataSlot* m_booleanSlot;

    BP_Parameter* m_booleanParameter;

    BP_FlowSlot* m_nextFlowSlot;

public:
    Q_INVOKABLE BP_IFNode();

    virtual QVariant toVariantBP();

    BP_FlowSlot* trueFlowSlot() const;
    BP_FlowSlot* falseFlowSlot() const;
    BP_FlowSlot* flowInSlot() const;

    BP_DataSlot* booleanSlot() const;

    BP_Parameter* booleanParameter() const;

public slots:
    void setTrueFlowSlot(BP_FlowSlot* trueFlowSlot);
    void setFalseFlowSlot(BP_FlowSlot* falseFlowSlot);

    void setFlowInSlot(BP_FlowSlot* flowInSlot);

    void setBooleanSlot(BP_DataSlot* booleanSlot);

    void setBooleanParameter(BP_Parameter* booleanParameter);

    void setNextFlowSlot(BP_FlowSlot* nextFlowSlot);

signals:
    void trueFlowSlotChanged(BP_FlowSlot* trueFlowSlot);
    void falseFlowSlotChanged(BP_FlowSlot* falseFlowSlot);
    void flowInSlotChanged(BP_FlowSlot* flowInSlot);
    void booleanSlotChanged(BP_DataSlot* booleanSlot);
    void booleanParameterChanged(BP_Parameter* booleanParameter);

    // QGraphicsItem interface
    void nextFlowSlotChanged(BP_FlowSlot* nextFlowSlot);

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
};

#endif // BP_IFNODE_H
