/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/

//NOTE: the operaitons node inheriting this class has no inside variable and render the
// output from the connected slots

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
    Q_PROPERTY(QString displayText READ displayText WRITE setDisplayText NOTIFY displayTextChanged)
    //TODO add a parameter to a uniqe class that will be accepted
    //TODO give the option to  change the current Class supported in the operation

    QList<BP_DataSlot*> m_inputSlots;
    BP_DataSlot* m_outputSlot;

    int m_maxNumberOfInputs;

    QString m_displayText;

public:
    BP_OperationToolNode();

    void addNewInput();

    QList<BP_DataSlot*> inputSlots() const;
    BP_DataSlot* outputSlot() const;

public slots:
    void setInputSlots(QList<BP_DataSlot*> inputSlots);
    void setOutputSlot(BP_DataSlot* outputSlot);
    void setMaxNumberOfInputs(int maxNumberOfInputs);

    void setDisplayText(QString displayText);

signals:
    void outputSlotChanged(BP_DataSlot* outputSlot);

    void maxNumberOfInputsChanged(int maxNumberOfInputs);

    void displayTextChanged(QString displayText);

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void calculateBounds() override;
    virtual BP_Node *nextNode() override;
    int maxNumberOfInputs() const;
    QString displayText() const;
};

#endif // BP_OPERATIONTOOLNODE_H
