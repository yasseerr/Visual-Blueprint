/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_STRINGNODE_H
#define BP_STRINGNODE_H

#include "bp_variablenode.h"

#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QObject>
#include <QTextEdit>

class BP_StringNode : public BP_VariableNode
{
    Q_OBJECT

    QLineEdit *m_textEdit;
    QGraphicsProxyWidget *m_textItem;

public:
    BP_StringNode(QObject *parent = nullptr);
    ~BP_StringNode();

public slots:
    void onTextChanged(QString text);

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // BP_Node interface
public:
    virtual void calculateBounds() override;
    virtual QString renderNode(BP_PlatformManager *platform) override;
    QString getNodeTypeString() override;
};

#endif // BP_STRINGNODE_H
