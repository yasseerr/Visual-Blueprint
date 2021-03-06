/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_EVENTNODE_H
#define BP_EVENTNODE_H

#include <QObject>

#include <Graph/bp_node.h>

class BP_FlowLink;
class BP_FlowSlot;

class BP_EventNode : public BP_Node
{
    Q_OBJECT
    Q_CLASSINFO("name","Event")
    Q_PROPERTY(QString eventName READ eventName WRITE setEventName NOTIFY eventNameChanged)
    QString m_eventName;


    QMap<QString, BP_FlowSlot *> eventFlows;
    QMap<BP_FlowSlot*,BP_FrameBranch*> slotsBranches;

public:
    Q_INVOKABLE BP_EventNode();
    static int nodeTypeID ;

    void addEventFlow(BP_FlowSlot *flow);
    BP_FlowSlot* getEventFlow(QString flowName);
    BP_FlowSlot* createFlow(QString flowName);

    QVariant toVariantBP() override;
    void fromVariant(QVariant var) override;

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // BP_Node interface
public:
    virtual void calculateBounds() override;
    QString renderNode(BP_PlatformManager *platform) override;
    BP_Node * nextNode() override;
    virtual QString getNodeTypeString() override;
    QString eventName() const;
public slots:
    void setEventName(QString eventName);
signals:
    void eventNameChanged(QString eventName);


};

#endif // BP_EVENTNODE_H
