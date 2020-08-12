/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_boolnode.h"

#include <QPainter>
#include <QSpinBox>
#include <bp_utils.h>

#include <Core/bp_variable.h>

#include <Graph/Slots/bp_dataslot.h>

#include <Platform/bp_platformmanager.h>

#include "Graph/bp_graphutils.h"

RegisterToolNodeType(BP_BoolNode,"Add Variable")

BP_BoolNode::BP_BoolNode():BP_VariableNode(),
m_boolCheckBox(new QCheckBox()),
m_boolItem(new QGraphicsProxyWidget())
{
    connect(m_boolCheckBox,&QCheckBox::stateChanged,this,&BP_BoolNode::onCheckedChange);
    //connect(m_boolCheckBox,SIGNAL(stateChanged(int)),this,SLOT(onCheckedChange(int)));
    m_boolCheckBox->setMouseTracking(false);
    qDebug("BoolNode created");
    m_boolItem->setParentItem(this);
    m_boolItem->setWidget(m_boolCheckBox);
    m_boolItem->setPos(0,0);
    m_boolItem->setGeometry(QRectF(3,3,24,24));

    //creating the variable
    BP_Variable *variable = new BP_Variable(nullptr,this);
    variable->setValue(false);
    variable->setIsMember(false);
    variable->setIsPrimitive(true);
    variable->setName("var_bool"+QString::number(nodeId));
    variable->setIsArray(false);
    variable->setIsImported(false);
    variable->setSourceClass(BP_Utils::instance()->currentProject->platformManager()->getBasicTypeClass("boolean"));

    setCoreObject(variable);
    setVariableObject(variable);
    connect(this,&BP_VariableNode::updateDisplay,
            [this](){this->m_boolCheckBox->setChecked(variableObject()->value().toBool());});
}

BP_BoolNode::~BP_BoolNode()
{

}

//QVariant BP_BoolNode::toVariantBP()
//{
//    QVariantMap retMap = BP_Node::toVariantBP().toMap();
//    retMap["type"] = getNodeTypeString();
//    retMap["variableValue"] = variableObject()->value();
//    retMap["outputSlot"] = m_outputSlot->toVariantBP();
//    return retMap;
//}



void BP_BoolNode::onCheckedChange(int value)
{
    variableObject()->setValue(value);
}

void BP_BoolNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QColor("orange"));
    painter->drawRect(boundingRect());
}

void BP_BoolNode::calculateBounds()
{
    m_bounds.setWidth(50);
    m_bounds.setHeight(30);
    m_bounds.setTopLeft(QPoint(0,0));
    outputSlot()->setPos(m_bounds.width()-17,5);
}

QString BP_BoolNode::renderNode(BP_PlatformManager *platform)
{
    CHECK_FIRST_REFERENCE
    return  platform->renderBoolNode(this);
}

QString BP_BoolNode::getNodeTypeString()
{
    return "Bool";
}

