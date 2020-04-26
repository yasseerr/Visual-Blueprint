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

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include <Graph/Links/bp_link.h>

#include <Core/bp_coreobject.h>

BP_Slot::BP_Slot(BP_Node *parent) : QObject(parent),m_parentNode(parent)
{
    setParentItem(parent);
}

QPointF BP_Slot::getAnchorPoint()
{
    return scenePos() + QPoint(7,7);
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

QList<BP_Link *> BP_Slot::connectedLinks() const
{
    return m_connectedLinks;
}

void BP_Slot::setParentNode(BP_Node *parentNode)
{
    if (m_parentNode == parentNode)
        return;

    m_parentNode = parentNode;
    emit parentNodeChanged(m_parentNode);
}

void BP_Slot::setConnectedLinks(QList<BP_Link *> connectedLinks)
{
    if (m_connectedLinks == connectedLinks)
        return;

    m_connectedLinks = connectedLinks;
    emit connectedLinksChanged(m_connectedLinks);
}

void BP_Slot::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "pressed at position" << event->pos();
    temporaryLink = new BP_Link();
    temporaryLink->setInSlot(this);
    this->scene()->addItem(temporaryLink);
}

void BP_Slot::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "mouse moved " << event->pos();
    temporaryLink->setTempOutputPoint(temporaryLink->mapFromScene(mapToScene(event->pos())));
    //TODO update only the rect arround the link
    scene()->update();
    //temporaryLink->update();
}

void BP_Slot::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "mouse released " << event->pos();
    BP_Slot *selectedItem =  dynamic_cast<BP_Slot*>(scene()->itemAt(event->scenePos(),QTransform()));
    if(selectedItem != nullptr){
        qDebug() << " selected item " << selectedItem->parentNode()->coreObject()->name();
        //TODO filter the allowed connection
        temporaryLink->setOutSlot(selectedItem);
        m_connectedLinks << temporaryLink;
    }
    else{
        scene()->removeItem(temporaryLink);
    }
    scene()->update();
}
