/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_intnode.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>

#include <Graph/Slots/bp_dataslot.h>

#include <Core/bp_parameter.h>
#include <Core/bp_variable.h>

#include <Platform/bp_platformmanager.h>


BP_IntNode::BP_IntNode():BP_VariableNode(),m_spinbox(new QSpinBox()),m_spinItem(new QGraphicsProxyWidget())
{
    //initiation of the spinbox
    m_spinbox->setValue(0);
    connect(m_spinbox,SIGNAL(valueChanged(int)),this,SLOT(onSpinBoxValueChanged(int)));

    m_spinItem->setParentItem(this);
    m_spinItem->setWidget(m_spinbox);
    m_spinItem->setPos(0,0);
    m_spinItem->setGeometry(QRectF(3,3,70,24));
    //scene()->addItem(m_spinItem);

    //creating the variable
    BP_Variable *intVariable = new BP_Variable(nullptr,this);
    intVariable->setValue(0);
    intVariable->setIsMember(false);
    intVariable->setIsPrimitive(true);
    intVariable->setName("varint");
    intVariable->setIsArray("false");

    setCoreObject(intVariable);
    setVariableObject(intVariable);

    outputSlot()->setReference("integer_"+QString::number(nodeId));

}

void BP_IntNode::onSpinBoxValueChanged(int val)
{
    variableObject()->setValue(val);
    qDebug() << "variable value : " << variableObject()->value().type() << " " << variableObject()->value();
}

void BP_IntNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkRed);
    painter->drawRect(boundingRect());
}

void BP_IntNode::calculateBounds()
{
    m_bounds.setWidth(100);
    m_bounds.setHeight(30);
    m_bounds.setTopLeft(QPoint(0,0));

    outputSlot()->setPos(m_bounds.width()-17,5);
}

QString BP_IntNode::renderNode(BP_PlatformManager *platform)
{
    return platform->renderIntegerNode(this);
}
