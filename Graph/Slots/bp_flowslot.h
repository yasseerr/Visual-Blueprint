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

    QPolygon trianglePolygone;
    bool m_isOutput;

public:
    BP_FlowSlot(BP_Node *parent = nullptr);

    virtual bool acceptConnection(BP_Slot *secondSlot) override;

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool isOutput() const;
public slots:
    void setIsOutput(bool isOutput);
signals:
    void isOutputChanged(bool isOutput);
};

#endif // BP_FLOWSLOT_H
