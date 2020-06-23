/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_FLOATNODE_H
#define BP_FLOATNODE_H

#include "bp_variablenode.h"

#include <QGraphicsProxyWidget>
#include <QObject>
#include <QSpinBox>

class BP_FloatNode : public BP_VariableNode
{
    Q_OBJECT

    QDoubleSpinBox *m_floatSpinBox;
    QGraphicsProxyWidget *m_floatItem;
public:
    BP_FloatNode();
    ~ BP_FloatNode();

public slots:
    void onValueChanged(double value);
    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void calculateBounds() override;

    // BP_Node interface
public:
    virtual QString renderNode(BP_PlatformManager *platform) override;
};

#endif // BP_FLOATNODE_H
