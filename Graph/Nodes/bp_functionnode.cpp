/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_functionnode.h"

#include <Graph/Slots/bp_dataslot.h>
#include <Graph/Slots/bp_flowslot.h>

#include <QDebug>
#include <QPainter>
#include <bp_utils.h>

#include <Core/bp_function.h>
#include <Core/bp_parameter.h>

#include <Platform/bp_platformmanager.h>

#include <Graph/Links/bp_link.h>

#include <Graph/bp_graphscene.h>
#include <Graph/bp_graphutils.h>
#include <Graph/bp_graphutils.h>
#include <Graph/bp_graphview.h>

RegisterNodeType(BP_FunctionNode)
BP_FunctionNode::BP_FunctionNode(QObject *parent):BP_Node(parent),m_selfSlot(nullptr)
{
    setNoFlowNode(false);
    //adding the execution flow
    m_executionflowInSlot = new BP_FlowSlot(this);
    m_executionflowInSlot->setParentItem(this);
    m_executionflowInSlot->setPos(2,7);
    m_executionflowInSlot->setIsOutput(false);
    m_executionflowInSlot->setShowFlowName(false);

    m_executionflowOutSlot = new BP_FlowSlot(this);
    m_executionflowOutSlot->setParentItem(this);
    m_executionflowOutSlot->setPos(2,7);
    m_executionflowOutSlot->setIsOutput(true);
    m_executionflowOutSlot->setShowFlowName(false);
}

QVariant BP_FunctionNode::toVariantBP()
{
    QVariantMap retMap = BP_Node::toVariantBP().toMap();
    retMap["type"] = getNodeTypeString();
    retMap["functionObject"] = m_functionObject?m_functionObject->toVariantBP():false;
    retMap["flowIn"] = m_executionflowInSlot->toVariantBP();
    retMap["flowOut"] = m_executionflowOutSlot->toVariantBP();
    retMap["returnSlot"] = m_returnSlot->toVariantBP();
    retMap["selfSlot"] = m_selfSlot?m_selfSlot->toVariantBP():false;

    QVariantList inputParametersVariant;
    foreach (auto inputVariant, m_inputParameters) {
        inputParametersVariant << inputVariant->toVariantBP();
    }
    retMap["inputtParameters"] = inputParametersVariant;
    return retMap;
}

void BP_FunctionNode::fromVariant(QVariant var)
{
    auto varMap =var.toMap();
    //TODO use the setCoreObjectFunction instead of setFunction to be able to use the parent map
    nodeId = varMap["nodeId"].toInt();
    BP_GraphUtils::getInstance()->registerNodeID(nodeId,this);
    //get the function object
    //auto _instatance = BP_Utils::instance();
    auto funcitonObjects = BP_Utils::instance()->coreObjectsMap.values(varMap["functionObject"].toMap()["name"].toString());
    //TODO compare the objects hierarchy when multiple objects are found
    foreach (auto functionObject, funcitonObjects) {
        //ignore if this
        if(functionObject == this->functionObject()) continue;
        qDebug()<<"funciton Object found " << functionObject->name() ;
        BP_Function* f =  qobject_cast<BP_Function*>(functionObject);
        if(!f)continue;
        setFunctionObject(f);
        setCoreObject(f);
    }
    m_executionflowInSlot->fromVariant(varMap["flowIn"]);
    m_executionflowOutSlot->fromVariant(varMap["flowOut"]);
    m_returnSlot->fromVariant(varMap["returnSlot"]);
    if(m_selfSlot) m_selfSlot->fromVariant(varMap["selfSlot"]);
    for (int i = 0; i < m_inputParameters.size(); ++i) {
        m_inputParameters.at(i)->fromVariant(varMap["inputtParameters"].toList().at(i));
    }
    setPos(varMap["scenePosX"].toFloat(),varMap["scenePosY"].toFloat());
}

void BP_FunctionNode::updateSlotsBranches(BP_Slot *slot)
{
    //for the inSlot
    if(!slot || slot== m_executionflowInSlot){
        auto joinedBranches = m_executionflowInSlot->getJoinedBranches();
        m_executionflowOutSlot->setFrameBranches(QList<BP_FrameBranch*>(joinedBranches));
        m_executionflowOutSlot->notifyConnectedNodes();

        //update the connected input nodes
        foreach (auto inputSlot, m_inputParameters) {
            inputSlot->setFrameBranches(joinedBranches);
            inputSlot->notifyConnectedNodes();
        }
    }

    //for the inputs

    //for the output
}

void BP_FunctionNode::connectSelfSlot(BP_Slot *selfSlot)
{
   BP_Link *selfLink = new BP_Link(selfSlot);
   selfSlot->addLink(selfLink);
   this->m_selfSlot->addLink(selfLink);
   selfLink->setInSlot(selfSlot);
   selfLink->setOutSlot(m_selfSlot);
   selfSlot->acceptConnection(m_selfSlot);
   auto graphScene = qobject_cast<BP_GraphScene*>(scene());
   connectedGraph()->scene()->addItem(selfLink);
}

void BP_FunctionNode::loadCurrentFunction()
{
    //loading outputs
    //Check that there is a valid outputd
    m_returnSlot = new BP_DataSlot(this);
    m_returnSlot->setParameterObject(m_functionObject->returnArg());
    m_returnSlot->setIsOutput(true);
    m_returnSlot->setReference(m_functionObject->name()+"Ret");

    //member slot
    if(m_functionObject->isMember()){
        m_selfSlot = new BP_DataSlot(this);
        //m_selfSlot->setShowName("self");
    }

    //input args
    foreach (auto param, m_functionObject->inputArgs()) {
        BP_DataSlot *inputSlot = new BP_DataSlot(this);
        inputSlot->setParameterObject(param);
        m_inputParameters << inputSlot;

    }
    //check the positional args

    //add the keyWords

}

BP_FlowSlot *BP_FunctionNode::executionflowInSlot() const
{
    return m_executionflowInSlot;
}

BP_FlowSlot *BP_FunctionNode::executionflowOutSlot() const
{
    return m_executionflowOutSlot;
}

QList<BP_DataSlot *> BP_FunctionNode::inputParameters() const
{
    return m_inputParameters;
}

BP_DataSlot *BP_FunctionNode::returnSlot() const
{
    return m_returnSlot;
}

BP_Function *BP_FunctionNode::functionObject() const
{
    return m_functionObject;
}

QString BP_FunctionNode::getNodeDocumentation()
{
    return BP_Node::getNodeDocumentation();
}

void BP_FunctionNode::setExecutionflowInSlot(BP_FlowSlot *executionflowInSlot)
{
    if (m_executionflowInSlot == executionflowInSlot)
        return;

    m_executionflowInSlot = executionflowInSlot;
    emit executionflowInSlotChanged(m_executionflowInSlot);
}

void BP_FunctionNode::setExecutionflowOutSlot(BP_FlowSlot *executionflowOutSlot)
{
    if (m_executionflowOutSlot == executionflowOutSlot)
        return;

    m_executionflowOutSlot = executionflowOutSlot;
    emit executionflowOutSlotChanged(m_executionflowOutSlot);
}

void BP_FunctionNode::setInputParameters(QList<BP_DataSlot *> inputParameters)
{
    if (m_inputParameters == inputParameters)
        return;

    m_inputParameters = inputParameters;
    emit inputParametersChanged(m_inputParameters);
}

void BP_FunctionNode::setReturnSlot(BP_DataSlot *returnSlot)
{
    if (m_returnSlot == returnSlot)
        return;

    m_returnSlot = returnSlot;
    emit returnSlotChanged(m_returnSlot);
}

void BP_FunctionNode::setFunctionObject(BP_Function *functionObject)
{
    if (m_functionObject == functionObject)
        return;
    m_functionObject = functionObject;
    loadCurrentFunction();
    m_executionflowInSlot->setFlowName("in_"+m_functionObject->name());
    m_executionflowOutSlot->setFlowName("out_"+m_functionObject->name());
    emit functionObjectChanged(m_functionObject);
}

void BP_FunctionNode::setSelfSlot(BP_DataSlot *selfSlot)
{
    if (m_selfSlot == selfSlot)
        return;

    m_selfSlot = selfSlot;
    emit selfSlotChanged(m_selfSlot);
}

void BP_FunctionNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Drawing the header
    painter->setBrush(Qt::darkBlue);
    painter->setPen(Qt::white);
    painter->drawRect(0,0,m_bounds.width(),30);
    painter->drawText(30,15,m_functionObject->name());

    //drawing the parameter section
    painter->setBrush(Qt::blue);
    //TODO put the name and the edit inside the slot item
    painter->drawRect(0,30,m_bounds.width(),m_bounds.height()-30);
    //parameters name
//    painter->drawText(0,40,"output");
//    for (int i = 0; i < m_inputParameters.size(); ++i) {
//        painter->drawText(30,50+i*20,m_inputParameters.at(i)->parameterObject()->parameterName());
//    }

}

void BP_FunctionNode::calculateBounds()
{
    //initial flow + name
    BP_Node::calculateBounds();
    int maxWidth = m_bounds.width() + 60;
    int maxHeight = 30;

    //output bound
    int outputWidth = 30 + QFontMetrics(QFont()).boundingRect("return").width();
    maxWidth = maxWidth>outputWidth? maxWidth:outputWidth;
    maxHeight += 30;

    //self variable bound
    if(functionObject()->isMember()){
        int outputWidth = 30 + QFontMetrics(QFont()).boundingRect("self").width();
        maxWidth = maxWidth>outputWidth? maxWidth:outputWidth;
        maxHeight += 30;
    }

    //parameter bounds
    foreach (auto paramSlot, m_inputParameters) {
        int paramWidth = 30 + QFontMetrics(QFont()).boundingRect(paramSlot->parameterObject()->parameterName()).width();
        maxWidth = maxWidth>paramWidth? maxWidth:paramWidth;
        maxHeight += 30;
    }
    maxHeight += 10;
    m_bounds.setHeight(maxHeight);
    m_bounds.setWidth(maxWidth);
    m_bounds.setX(0);
    m_bounds.setY(0);
    //setting the child items position
    m_returnSlot->setPos(m_bounds.width()-m_returnSlot->boundingRect().width(),30);
    if(functionObject()->isMember()){
        m_selfSlot->setPos(3,60);
    }
    m_executionflowOutSlot->setPos(m_bounds.width()-15,7);
    for (int i = 0; i < m_inputParameters.size(); ++i) {
        m_inputParameters.at(i)->setPos(3,(m_functionObject->isMember()?90:60)+30*i);
    }

}

QString BP_FunctionNode::renderNode(BP_PlatformManager *platform)
{
    CHECK_FIRST_REFERENCE
    return platform->renderFunctionNode(this);

}

BP_Node *BP_FunctionNode::nextNode()
{
    if(m_executionflowOutSlot->connectedLinks().size()==0) return nullptr;
    return m_executionflowOutSlot->connectedLinks().first()->outSlot()->parentNode();
}

BP_DataSlot *BP_FunctionNode::selfSlot() const
{
    return m_selfSlot;
}

QString BP_FunctionNode::getNodeTypeString()
{
    return "Function";
}

void BP_FunctionNode::mapInputFlowToOutput()
{
    m_executionflowOutSlot->setBranches(BP_GraphUtils::getInstance()->
                                        getReplacedSubBranchesWithParents(m_executionflowInSlot));
    BP_GraphUtils::getInstance()->setNodeParentBranches(this,m_executionflowOutSlot->branches());
}
