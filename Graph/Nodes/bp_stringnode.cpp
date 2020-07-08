/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_stringnode.h"

#include <Graph/Slots/bp_dataslot.h>

#include <QPainter>

#include <Core/bp_variable.h>

#include <Platform/bp_platformmanager.h>
#include "Graph/bp_graphutils.h"

RegisterToolNodeType(BP_StringNode,"Add Variable")


BP_StringNode::BP_StringNode(QObject *parent):BP_VariableNode(),m_textEdit(new QLineEdit("")),m_textItem(new QGraphicsProxyWidget())
{
    //initiation of the textedit
    m_textEdit->setText("");
    m_textEdit->setPlaceholderText("Enter String text");
    connect(m_textEdit,SIGNAL(textChanged(QString)),this,SLOT(onTextChanged(QString)));

    m_textItem->setParentItem(this);
    m_textItem->setWidget(m_textEdit);
    m_textItem->setPos(0,0);
    m_textItem->setGeometry(QRectF(3,3,70,24));
    //scene()->addItem(m_spinItem);

    //creating the variable
    BP_Variable *variable = new BP_Variable(nullptr,this);
    variable->setValue("");
    variable->setIsMember(false);
    variable->setIsPrimitive(true);
    variable->setName("varstring_"+QString::number(nodeId));
    variable->setIsArray("false");

    setCoreObject(variable);
    setVariableObject(variable);
}


BP_StringNode::~BP_StringNode()
{

}

void BP_StringNode::onTextChanged(QString text)
{
    variableObject()->setValue(text);
}

void BP_StringNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkMagenta);
    painter->drawRect(boundingRect());
}

void BP_StringNode::calculateBounds()
{
    m_bounds.setWidth(100);
    m_bounds.setHeight(30);
    m_bounds.setTopLeft(QPoint(0,0));

    outputSlot()->setPos(m_bounds.width()-17,5);

}

QString BP_StringNode::renderNode(BP_PlatformManager *platform)
{
    CHECK_FIRST_REFERENCE
    return  platform->renderStringNode(this);
}

QString BP_StringNode::getNodeTypeString()
{
    return "String";
}
