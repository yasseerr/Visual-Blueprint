/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_node.h"
#include "bp_slot.h"

#include <QPainter>

BP_Slot::BP_Slot(BP_Node *parent) : QObject(parent),m_parentNode(parent)
{
    setParentItem(parent);
}

QRectF BP_Slot::boundingRect() const
{
    return QRectF(0,0,15,15);
}

void BP_Slot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(boundingRect());

}

BP_Node *BP_Slot::parentNode() const
{
    return m_parentNode;
}

void BP_Slot::setParentNode(BP_Node *parentNode)
{
    if (m_parentNode == parentNode)
        return;

    m_parentNode = parentNode;
    emit parentNodeChanged(m_parentNode);
}
