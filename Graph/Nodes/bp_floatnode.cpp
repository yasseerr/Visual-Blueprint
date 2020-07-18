/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_floatnode.h"

#include <QPainter>
#include <QSpinBox>

#include <Core/bp_variable.h>

#include <Graph/Slots/bp_dataslot.h>

#include <Platform/bp_platformmanager.h>

#include "Graph/bp_graphutils.h"

RegisterToolNodeType(BP_FloatNode,"Add Variable")

BP_FloatNode::BP_FloatNode():BP_VariableNode(),m_floatSpinBox(new QDoubleSpinBox()),m_floatItem(new QGraphicsProxyWidget())
{
    connect(m_floatSpinBox,SIGNAL(valueChanged(double)),this,SLOT(onValueChanged(double)));
    //connect(m_floatSpinBox,&QDoubleSpinBox::valueChanged,this,&BP_FloatNode::onValueChanged);
    qDebug("double spinbox created");
    m_floatItem->setParentItem(this);
    m_floatItem->setWidget(m_floatSpinBox);
    m_floatItem->setPos(0,0);
    m_floatItem->setGeometry(QRectF(3,3,70,24));
    //scene()->addItem(m_spinItem);

    //creating the variable
    BP_Variable *variable = new BP_Variable(nullptr,this);
    variable->setValue(0.0);
    variable->setIsMember(false);
    variable->setIsPrimitive(true);
    variable->setName("var_float"+QString::number(nodeId));
    variable->setIsArray("false");
    variable->setIsImported(false);

    setCoreObject(variable);
    setVariableObject(variable);

    connect(this,&BP_VariableNode::updateDisplay,
            [this](){this->m_floatSpinBox->setValue(variableObject()->value().toFloat());});
}

BP_FloatNode::~BP_FloatNode()
{

}

void BP_FloatNode::onValueChanged(double value)
{
    variableObject()->setValue(value);
}

void BP_FloatNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QColor("orange"));
    painter->drawRect(boundingRect());
}

void BP_FloatNode::calculateBounds()
{
    m_bounds.setWidth(100);
    m_bounds.setHeight(30);
    m_bounds.setTopLeft(QPoint(0,0));
    outputSlot()->setPos(m_bounds.width()-17,5);
}

QString BP_FloatNode::renderNode(BP_PlatformManager *platform)
{
    CHECK_FIRST_REFERENCE
    return platform->renderFloatNode(this);
}

QString BP_FloatNode::getNodeTypeString()
{
    return "Float";
}
