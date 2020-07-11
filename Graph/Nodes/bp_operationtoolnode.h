/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_OPERATIONTOOLNODE_H
#define BP_OPERATIONTOOLNODE_H

#include <QObject>

#include <Graph/bp_node.h>

class BP_DataSlot;

class BP_OperationToolNode : public BP_Node
{
    Q_OBJECT
    Q_CLASSINFO("name","Operation Tool")
    Q_PROPERTY(QList<BP_DataSlot*> inputSlots READ inputSlots WRITE setInputSlots)
    Q_PROPERTY(BP_DataSlot* outputSlot READ outputSlot WRITE setOutputSlot NOTIFY outputSlotChanged)
    Q_PROPERTY(int maxNumberOfInputs READ maxNumberOfInputs WRITE setMaxNumberOfInputs NOTIFY maxNumberOfInputsChanged)
    //TODO add a parameter to a uniqe class that will be accepted
    //TODO give the option to  change the current Class supported in the operation

    QList<BP_DataSlot*> m_inputSlots;
    BP_DataSlot* m_outputSlot;

    int m_maxNumberOfInputs;

public:
    BP_OperationToolNode();

    void addNewInput();

    QList<BP_DataSlot*> inputSlots() const;
    BP_DataSlot* outputSlot() const;

public slots:
    void setInputSlots(QList<BP_DataSlot*> inputSlots);
    void setOutputSlot(BP_DataSlot* outputSlot);
    void setMaxNumberOfInputs(int maxNumberOfInputs)
    {
        if (m_maxNumberOfInputs == maxNumberOfInputs)
            return;

        m_maxNumberOfInputs = maxNumberOfInputs;
        emit maxNumberOfInputsChanged(m_maxNumberOfInputs);
    }

signals:
    void outputSlotChanged(BP_DataSlot* outputSlot);

    void maxNumberOfInputsChanged(int maxNumberOfInputs);

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void calculateBounds() override;
virtual BP_Node *nextNode() override;
int maxNumberOfInputs() const
{
    return m_maxNumberOfInputs;
}
};

#endif // BP_OPERATIONTOOLNODE_H
