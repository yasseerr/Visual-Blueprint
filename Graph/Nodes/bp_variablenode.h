/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_VARIABLENODE_H
#define BP_VARIABLENODE_H

#include <QObject>

#include <Graph/bp_node.h>

class BP_Variable;
class BP_DataSlot;

class BP_VariableNode : public BP_Node
{
    Q_OBJECT
    Q_CLASSINFO("name","Variable")
    Q_PROPERTY(BP_Variable* variableObject READ variableObject WRITE setVariableObject NOTIFY variableObjectChanged)
    Q_PROPERTY(BP_DataSlot* outputSlot READ outputSlot WRITE setOutputSlot NOTIFY outputSlotChanged)

    BP_Variable* m_variableObject;

    BP_DataSlot* m_outputSlot;


public:
    Q_INVOKABLE BP_VariableNode();

    //used to be able to call the macros in bp_graph_utils
    static int nodeTypeID ;

    QVariant toVariantBP() override;
    void fromVariant(QVariant var) override;

    void updateSlotsBranches(BP_Slot *slot) override;
    // QGraphicsItem interface
public:
    void calculateBounds() override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    BP_Variable* variableObject() const;
    BP_DataSlot* outputSlot() const;

    QString getNodeTypeString() override;
    QString renderNode(BP_PlatformManager *platform) override;


public slots:
    void setVariableObject(BP_Variable* variableObject);
    void setOutputSlot(BP_DataSlot* outputSlot);


signals:
    void variableObjectChanged(BP_Variable* variableObject);
    void outputSlotChanged(BP_DataSlot* outputSlot);

    void updateDisplay();
};

#endif // BP_VARIABLENODE_H
