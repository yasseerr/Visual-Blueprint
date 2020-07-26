/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_loopnode.h"
#include <Graph/bp_graphutils.h>
#include <Graph/Slots/bp_dataslot.h>
#include <Graph/Slots/bp_flowslot.h>
#include <Core/bp_parameter.h>
#include <QPainter>
#include <Graph/Links/bp_link.h>
#include <Platform/bp_platformmanager.h>


RegisterToolNodeType(BP_LoopNode,"Programing")
BP_LoopNode::BP_LoopNode():BP_Node(),
    m_flowInSlot(new BP_FlowSlot(this)),
    m_flowOutSlot(new BP_FlowSlot(this)),
    m_loopFlowSlot(new BP_FlowSlot(this)),
    m_startValueSlot(new BP_DataSlot(this)),
    m_endValueSlot(new BP_DataSlot(this)),
    m_stepSlot(new BP_DataSlot(this)),
    m_counterSlot(new BP_DataSlot(this)),
    m_startParameter(new BP_Parameter(this)),
    m_endParameter(new BP_Parameter(this)),
    m_stepParameter(new BP_Parameter(this)),
    m_counterParameter(new BP_Parameter(this))
{
    setNoFlowNode(false);

    //the next node will be used later
    m_flowOutSlot->setIsOutput(true);
    m_flowOutSlot->setFlowName("out");
    m_flowOutSlot->setShowFlowName(false);
    m_flowOutSlot->setParentItem(this);
    m_flowOutSlot->setParentNode(this);

    m_flowInSlot->setIsOutput(false);
    m_flowInSlot->setShowFlowName(false);
    m_flowInSlot->setParentItem(this);
    m_flowInSlot->setParentNode(this);

    m_loopFlowSlot->setIsOutput(true);
    m_loopFlowSlot->setShowFlowName(true);
    m_loopFlowSlot->setParentItem(this);
    m_loopFlowSlot->setParentNode(this);
    m_loopFlowSlot->setFlowName("loop entry");

    m_startParameter->setParameterName("start");
    m_endParameter->setParameterName("end");
    m_stepParameter->setParameterName("step");

    m_startParameter->setIsImported(false);
    m_endParameter->setIsImported(false);
    m_stepParameter->setIsImported(false);
    m_counterParameter->setIsImported(false);
    m_counterParameter->setParameterName("counter");

    m_startValueSlot->setShowName(true);
    m_startValueSlot->setParameterObject(m_startParameter);
    m_startValueSlot->setIsOutput(false);
    m_startValueSlot->setParentItem(this);

    m_endValueSlot->setShowName(true);
    m_endValueSlot->setParameterObject(m_endParameter);
    m_endValueSlot->setIsOutput(false);
    m_endValueSlot->setParentItem(this);

    m_stepSlot->setShowName(true);
    m_stepSlot->setParameterObject(m_stepParameter);
    m_stepSlot->setIsOutput(false);
    m_stepSlot->setParentItem(this);

    m_counterSlot->setShowName(true);
    m_counterSlot->setParameterObject(m_stepParameter);
    m_counterSlot->setIsOutput(true);
    m_counterSlot->setParentItem(this);
    m_counterSlot->setReference("i_"+QString::number(nodeId));
    m_counterSlot->setReturnName("counter");
    m_counterSlot->setParameterObject(m_counterParameter);

    this->calculateBounds();

}

QVariant BP_LoopNode::toVariantBP()
{
    QVariantMap retMap = BP_Node::toVariantBP().toMap();
    retMap["type"] = getNodeTypeString();

    retMap["flowInSlot"] = m_flowInSlot->toVariantBP();
    retMap["flowOutSlot"] = m_flowOutSlot->toVariantBP();
    retMap["loopFlowSlot"] = m_loopFlowSlot->toVariantBP();
    retMap["counterSlot"] = m_counterSlot->toVariantBP();
    retMap["startSlot"] = m_startValueSlot->toVariantBP();
    retMap["endSlot"] = m_endValueSlot->toVariantBP();
    retMap["stepSlot"] = m_stepSlot->toVariantBP();


    return retMap;
}

void BP_LoopNode::fromVariant(QVariant var)
{
    BP_Node::fromVariant(var);
    auto varMap  = var.toMap();

    m_flowInSlot->fromVariant(varMap["flowInSlot"]);
    m_flowOutSlot->fromVariant(varMap["flowOutSlot"]);
    m_loopFlowSlot->fromVariant(varMap["loopFlowSlot"]);
    m_counterSlot->fromVariant(varMap["counterSlot"]);
    m_startValueSlot->fromVariant(varMap["startSlot"]);
    m_endValueSlot->fromVariant(varMap["endSlot"]);
    m_stepSlot->fromVariant(varMap["stepSlot"]);
}

void BP_LoopNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QColor(Qt::GlobalColor::gray));
    painter->drawRect(boundingRect());

    painter->setPen(Qt::white);
    painter->setOpacity(0.8);
    painter->drawText(QPoint(boundingRect().center().x()-15,15),"loop");

}

void BP_LoopNode::calculateBounds()
{
    BP_Node::calculateBounds();
    int maxWidth = 0;
    int maxHeight = 180;

    //output bound
    int outputWidth =30+ m_flowInSlot->boundingRect().width()*2 + QFontMetrics(QFont()).boundingRect("Loop").width();
    maxWidth = maxWidth>outputWidth? maxWidth:outputWidth;


    //parameter bounds
    maxWidth = m_loopFlowSlot->boundingRect().width()>maxWidth?m_loopFlowSlot->boundingRect().width():maxWidth;
    maxWidth = m_startValueSlot->boundingRect().width()>maxWidth?m_loopFlowSlot->boundingRect().width():maxWidth;
    maxWidth = m_endValueSlot->boundingRect().width()>maxWidth?m_loopFlowSlot->boundingRect().width():maxWidth;
    maxWidth = m_stepSlot->boundingRect().width()>maxWidth?m_loopFlowSlot->boundingRect().width():maxWidth;
    maxWidth = m_counterSlot->boundingRect().width()>maxWidth?m_counterSlot->boundingRect().width():maxWidth;

    m_bounds.setHeight(maxHeight);
    m_bounds.setWidth(maxWidth);
    m_bounds.setX(0);
    m_bounds.setY(0);
    //setting the child items position
    m_loopFlowSlot->setPos(m_bounds.width()-m_loopFlowSlot->boundingRect().width(),30);
    m_counterSlot->setPos(m_bounds.width()-m_counterSlot->boundingRect().width(),60);
    m_startValueSlot->setPos(5,90);
    m_endValueSlot->setPos(5,120);
    m_stepSlot->setPos(5,150);

    m_flowOutSlot->setPos(5+m_bounds.width()-m_flowInSlot->boundingRect().width(),7);
    m_flowInSlot->setPos(5,7);


}

QString BP_LoopNode::renderNode(BP_PlatformManager *platform)
{
    CHECK_FIRST_REFERENCE
    return platform->renderLoopStatement(this);
}

BP_Node *BP_LoopNode::nextNode()
{
    if(m_flowOutSlot->connectedLinks().size()==0) return nullptr;
    return m_flowOutSlot->connectedLinks().first()->outSlot()->parentNode();
}

QString BP_LoopNode::getNodeTypeString()
{
    return "loop";
}

BP_FlowSlot *BP_LoopNode::nextFlowSlot() const
{
    return nullptr;
}

void BP_LoopNode::mapInputFlowToOutput()
{
    //return "Loop";
}

BP_FlowSlot *BP_LoopNode::flowInSlot() const
{
    return m_flowInSlot;
}

BP_FlowSlot *BP_LoopNode::flowOutSlot() const
{
    return m_flowOutSlot;
}

BP_DataSlot *BP_LoopNode::startValueSlot() const
{
    return m_startValueSlot;
}

BP_DataSlot *BP_LoopNode::endValueSlot() const
{
    return m_endValueSlot;
}

BP_DataSlot *BP_LoopNode::stepSlot() const
{
    return m_stepSlot;
}

BP_FlowSlot *BP_LoopNode::loopFlowSlot() const
{
    return m_loopFlowSlot;
}

BP_DataSlot *BP_LoopNode::counterSlot() const
{
    return m_counterSlot;
}

void BP_LoopNode::setFlowInSlot(BP_FlowSlot *flowInSlot)
{
    if (m_flowInSlot == flowInSlot)
        return;

    m_flowInSlot = flowInSlot;
    emit flowInSlotChanged(m_flowInSlot);
}

void BP_LoopNode::setFlowOutSlot(BP_FlowSlot *flowOutSlot)
{
    if (m_flowOutSlot == flowOutSlot)
        return;

    m_flowOutSlot = flowOutSlot;
    emit flowOutSlotChanged(m_flowOutSlot);
}

void BP_LoopNode::setStartValueSlot(BP_DataSlot *startValueSlot)
{
    if (m_startValueSlot == startValueSlot)
        return;

    m_startValueSlot = startValueSlot;
    emit startValueSlotChanged(m_startValueSlot);
}

void BP_LoopNode::setEndValueSlot(BP_DataSlot *endValueSlot)
{
    if (m_endValueSlot == endValueSlot)
        return;

    m_endValueSlot = endValueSlot;
    emit endValueSlotChanged(m_endValueSlot);
}

void BP_LoopNode::setStepSlot(BP_DataSlot *stepSlot)
{
    if (m_stepSlot == stepSlot)
        return;

    m_stepSlot = stepSlot;
    emit stepSlotChanged(m_stepSlot);
}

void BP_LoopNode::setLoopFlowSlot(BP_FlowSlot *loopFlowSlot)
{
    if (m_loopFlowSlot == loopFlowSlot)
        return;

    m_loopFlowSlot = loopFlowSlot;
    emit loopFlowSlotChanged(m_loopFlowSlot);
}

void BP_LoopNode::setCounterSlot(BP_DataSlot *counterSlot)
{
    if (m_counterSlot == counterSlot)
        return;

    m_counterSlot = counterSlot;
    emit counterSlotChanged(m_counterSlot);
}
