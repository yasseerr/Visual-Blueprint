/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_BOOLNODE_H
#define BP_BOOLNODE_H


#include "bp_variablenode.h"

#include <QGraphicsProxyWidget>
#include <QObject>
#include <QCheckBox>

class BP_BoolNode : public BP_VariableNode
{
    Q_OBJECT
    Q_CLASSINFO("name","Bool")
    QCheckBox *m_boolCheckBox;
    QGraphicsProxyWidget *m_boolItem;
public:
    Q_INVOKABLE BP_BoolNode();
    ~ BP_BoolNode();

    //QVariant toVariantBP() override;

    static int nodeTypeID ;

public slots:
    void onCheckedChange(int value);
    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void calculateBounds() override;

    // BP_Node interface
public:
    virtual QString renderNode(BP_PlatformManager *platform) override;
    QString getNodeTypeString() override;
};

#endif // BP_BOOLNODE_H


