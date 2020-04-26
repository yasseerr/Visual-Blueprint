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

class BP_Slot;

class BP_Link :public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(BP_Slot* inSlot READ inSlot WRITE setInSlot NOTIFY inSlotChanged)
    Q_PROPERTY(BP_Slot* outSlot READ outSlot WRITE setOutSlot NOTIFY outSlotChanged)

    BP_Slot* m_inSlot;
    BP_Slot* m_outSlot;

public:
    BP_Link(QObject *parent = nullptr);

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


    BP_Slot* inSlot() const;
    BP_Slot* outSlot() const;

public slots:
    void setInSlot(BP_Slot* inSlot);
    void setOutSlot(BP_Slot* outSlot);

signals:
    void inSlotChanged(BP_Slot* inSlot);
    void outSlotChanged(BP_Slot* outSlot);
};

#endif // BP_LINK_H
