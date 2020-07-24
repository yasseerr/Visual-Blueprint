/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_LINK_H
#define BP_LINK_H

#include <QGraphicsItem>
#include <QObject>

#include <Graph/bp_slot.h>

class BP_Slot;


class BP_Link :public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(BP_Slot* inSlot READ inSlot WRITE setInSlot NOTIFY inSlotChanged)
    Q_PROPERTY(BP_Slot* outSlot READ outSlot WRITE setOutSlot NOTIFY outSlotChanged)
    Q_PROPERTY(QPointF tempOutputPoint READ tempOutputPoint WRITE setTempOutputPoint NOTIFY tempOutputPointChanged)

    BP_Slot* m_inSlot;
    BP_Slot* m_outSlot;


    QPointF m_tempOutputPoint;
    QPointF m_inSlotPoint;
    QPointF m_outSlotPoint;

public:
    BP_Link(QObject *parent = nullptr);

    virtual QVariant toVariantBP();
    virtual void fromVariant(QVariant var);

    void disconnectSlot(BP_Slot *slot);
    void disconnectAllSlots();
    BP_Slot* getTheOneConnectedSlot();

    void drawCubicCurve(QPainter *painter,QPointF c1,QPointF c2,QPointF startPoint ,QPointF endPoint);

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


    BP_Slot* inSlot() const;
    BP_Slot* outSlot() const;

    QPointF tempOutputPoint() const;

public slots:
    void setInSlot(BP_Slot* inSlot);
    void setOutSlot(BP_Slot* outSlot);

    void setTempOutputPoint(QPointF tempOutputPoint);

signals:
    void inSlotChanged(BP_Slot* inSlot);
    void outSlotChanged(BP_Slot* outSlot);
    void tempOutputPointChanged(QPointF tempOutputPoint);
};
//Q_DECLARE_METATYPE(BP_Link*)
//Q_DECLARE_METATYPE(QList<BP_Link*>)

#endif // BP_LINK_H
