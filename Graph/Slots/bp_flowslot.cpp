/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_flowslot.h"

#include <qpainter.h>

BP_FlowSlot::BP_FlowSlot(BP_Node *parent):BP_Slot(parent)
{
    trianglePolygone << QPoint(0,0) << QPoint(0,14) << QPoint(12,7);
}

void BP_FlowSlot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setBrush(Qt::white);
    painter->drawPolygon(trianglePolygone);

}