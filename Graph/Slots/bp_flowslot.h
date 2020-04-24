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


    QPolygon trianglePolygone;
public:
    BP_FlowSlot(BP_Node *parent = nullptr);

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // BP_FLOWSLOT_H
