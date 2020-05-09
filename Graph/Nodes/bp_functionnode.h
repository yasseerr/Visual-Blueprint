/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_FUNCTIONNODE_H
#define BP_FUNCTIONNODE_H

#include <QObject>
#include <QPushButton>

#include <Graph/bp_node.h>

#include <Graph/Slots/bp_dataslot.h>

#include <Core/bp_function.h>

//class BP_Function;
class BP_FlowSlot;
//class BP_DataSlot;
Q_DECLARE_METATYPE(QList<BP_DataSlot*>)
class BP_FunctionNode : public BP_Node
{
    Q_OBJECT
    //TODO add support for multiple flow inputs/outputs
    Q_PROPERTY(BP_FlowSlot* executionflowInSlot READ executionflowInSlot WRITE setExecutionflowInSlot NOTIFY executionflowInSlotChanged)
    Q_PROPERTY(BP_FlowSlot* executionflowOutSlot READ executionflowOutSlot WRITE setExecutionflowOutSlot NOTIFY executionflowOutSlotChanged)
    Q_PROPERTY(QList<BP_DataSlot*> inputParameters READ inputParameters WRITE setInputParameters NOTIFY inputParametersChanged)
    Q_PROPERTY(BP_DataSlot* returnSlot READ returnSlot WRITE setReturnSlot NOTIFY returnSlotChanged)
    Q_PROPERTY(BP_DataSlot* selfSlot READ selfSlot WRITE setSelfSlot NOTIFY selfSlotChanged)
    Q_PROPERTY(BP_Function* functionObject READ functionObject WRITE setFunctionObject NOTIFY functionObjectChanged)

    BP_FlowSlot* m_executionflowInSlot;
    BP_FlowSlot* m_executionflowOutSlot;
    QList<BP_DataSlot*> m_inputParameters;
    BP_DataSlot* m_returnSlot;
    BP_Function* m_functionObject;

private:
    QPushButton *addPositionalParameterButton;
    //TODO work out how to add the keywords

    BP_DataSlot* m_selfSlot;

public:
    BP_FunctionNode(QObject *parent = nullptr);

public:

    void loadCurrentFunction();

    BP_FlowSlot* executionflowInSlot() const;
    BP_FlowSlot* executionflowOutSlot() const;

    QList<BP_DataSlot*> inputParameters() const;
    BP_DataSlot* returnSlot() const;

    BP_Function* functionObject() const;

public slots:
    void setExecutionflowInSlot(BP_FlowSlot* executionflowInSlot);
    void setExecutionflowOutSlot(BP_FlowSlot* executionflowOutSlot);
    void setInputParameters(QList<BP_DataSlot*> inputParameters);
    void setReturnSlot(BP_DataSlot* returnSlot);
    void setFunctionObject(BP_Function* functionObject);

    void setSelfSlot(BP_DataSlot* selfSlot);

signals:
    void executionflowInSlotChanged(BP_FlowSlot* executionflowInSlot);
    void executionflowOutSlotChanged(BP_FlowSlot* executionflowOutSlot);
    void inputParametersChanged(QList<BP_DataSlot*> inputParameters);
    void returnSlotChanged(BP_DataSlot* returnSlot);
    void functionObjectChanged(BP_Function* functionObject);

    // QGraphicsItem interface
    void selfSlotChanged(BP_DataSlot* selfSlot);

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void calculateBounds() override;
    QString renderNode(BP_PlatformManager *platform) override;
    BP_Node * nextNode() override;
    BP_DataSlot* selfSlot() const;
};

#endif // BP_FUNCTIONNODE_H
