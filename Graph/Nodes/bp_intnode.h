/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_INTNODE_H
#define BP_INTNODE_H

#include "bp_variablenode.h"

#include <QGraphicsProxyWidget>
#include <QObject>
#include <QSpinBox>

class BP_IntNode : public BP_VariableNode
{
    Q_OBJECT

    QSpinBox *m_spinbox;
    QGraphicsProxyWidget *m_spinItem;
public:
    BP_IntNode();

public slots:
    void onSpinBoxValueChanged(int val);

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // BP_Node interface
public:
    virtual void calculateBounds() override;
};

#endif // BP_INTNODE_H
