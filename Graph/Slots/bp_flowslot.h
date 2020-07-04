/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_FLOWSLOT_H
#define BP_FLOWSLOT_H

#include <QObject>

#include <Graph/bp_slot.h>

class BP_FlowSlot : public BP_Slot
{
    Q_OBJECT
    Q_PROPERTY(bool isOutput READ isOutput WRITE setIsOutput NOTIFY isOutputChanged)
    Q_PROPERTY(QString flowName READ flowName WRITE setFlowName NOTIFY flowNameChanged)
    Q_PROPERTY(bool showFlowName READ showFlowName WRITE setShowFlowName NOTIFY showFlowNameChanged)
    Q_PROPERTY(QList<int> branches READ branches WRITE setBranches NOTIFY branchesChanged)

    QPolygon trianglePolygone;
    bool m_isOutput;

    QString m_flowName;

    bool m_showFlowName;

    int flowNameWidth = 0;

    //the branches going into the slot
    QList<int> m_branches;

public:
    BP_FlowSlot(BP_Node *parent = nullptr);

    virtual bool acceptConnection(BP_Slot *secondSlot) override;

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override;
    virtual QPointF getAnchorPoint() override;
    bool isOutput() const;
    QString flowName() const;
    bool showFlowName() const;

    QList<int> branches() const;

public slots:
    void setIsOutput(bool isOutput);
    void setFlowName(QString flowName);
    void setShowFlowName(bool showFlowName);

    void setBranches(QList<int> branches);

signals:
    void isOutputChanged(bool isOutput);
    void flowNameChanged(QString flowName);
    void showFlowNameChanged(bool showFlowName);


    void branchesChanged(QList<int> branches);
};

#endif // BP_FLOWSLOT_H
