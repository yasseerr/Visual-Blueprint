/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_classinstancenode.h"

#include <Core/bp_constructor.h>
#include <Core/bp_parameter.h>
#include <Core/bp_variable.h>
#include "Graph/bp_graphutils.h"
#include "Core/bp_class.h"
#include <QDebug>
#include <QPainter>
#include <bp_utils.h>
#include <Graph/Slots/bp_dataslot.h>
#include <Platform/bp_platformmanager.h>
#include <Graph/Links/bp_link.h>

//RegisterToolNodeType(BP_ClassInstanceNode,"Add Variable")
RegisterNodeType(BP_ClassInstanceNode)
BP_ClassInstanceNode::BP_ClassInstanceNode():BP_VariableNode(),m_sourceClass(nullptr),m_constructorId(0)
{
    //the variable is created when the class is set


}

QVariant BP_ClassInstanceNode::toVariantBP()
{
    QVariantMap retMap = BP_Node::toVariantBP().toMap();
    retMap["type"] = getNodeTypeString();
    retMap["sourceClass"] = m_sourceClass->toVariantBP();
    retMap["outputSlot"] = outputSlot()->toVariantBP();

    retMap["constructorId"] = m_constructorId;

    QVariantList inputParametersVariant;
    foreach (auto inputVariant, m_inputParameters) {
        inputParametersVariant << inputVariant->toVariantBP();
    }
    retMap["inputtParameters"] = inputParametersVariant;
    return retMap;

}

void BP_ClassInstanceNode::fromVariant(QVariant var)
{
    BP_Node::fromVariant(var);
    auto varMap = var.toMap();
    //get the source class
    auto sourceClassVar = varMap["sourceClass"].toMap();
    auto coreObjects = BP_Utils::instance()
            ->coreObjectsMap.values(sourceClassVar["name"].toString());
    //TODO compare the objects hierarchy when multiple objects are found
    foreach (auto coreObject, coreObjects) {
        qDebug()<<"class Object found " << coreObject->name();
        setSourceClass(qobject_cast<BP_Class*>(coreObject));
    }
    outputSlot()->fromVariant(varMap["outputSlot"]);

    setConstructorId(varMap["constructorId"].toInt());

    for (int i = 0; i < m_inputParameters.size(); ++i) {
        m_inputParameters.at(i)->fromVariant(varMap["inputtParameters"].toList().at(i));
    }

    calculateBounds();
    //TODO test the laoding of  a class instance

}

QString BP_ClassInstanceNode::getNodeTypeString()
{
    return "Instance";
}

void BP_ClassInstanceNode::updateSlotsBranches(BP_Slot *slot)
{
    if(slot == outputSlot()){
        foreach (auto link, outputSlot()->connectedLinks()) {
            outputSlot()->m_frameBranches.unite(link->outSlot()->frameBranches());
        }
        foreach (auto inputSlot, m_inputParameters) {
            inputSlot->m_frameBranches.clear();
            inputSlot->m_frameBranches.unite(outputSlot()->frameBranches());
            inputSlot->notifyConnectedNodes();
        }
    }
}

void BP_ClassInstanceNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Drawing the header
    painter->setBrush(Qt::darkGreen);
    painter->setPen(Qt::white);
    painter->drawRect(0,0,m_bounds.width(),30);
    painter->drawText(30,15,":"+m_sourceClass->name());

    painter->setBrush(QColor("#74923A"));
    painter->drawRect(0,30,m_bounds.width(),m_bounds.height()-30);
}

void BP_ClassInstanceNode::calculateBounds()
{
    //initial flow + name
    BP_Node::calculateBounds();
    int maxWidth = m_bounds.width() + 60;
    int maxHeight = 30;

    //output bound
    //outputSlot()->setReference("Instance");
    outputSlot()->setShowName(true);
    outputSlot()->setTextColor(Qt::white);
    outputSlot()->setReturnName("Instance");
    //int outputWidth = 30 + QFontMetrics(QFont()).boundingRect("Instance").width();
    int outputWidth = 30 + outputSlot()->boundingRect().width();
    maxWidth = maxWidth>outputWidth? maxWidth:outputWidth;
    maxHeight += 30;

//    //self variable bound
//    if(functionObject()->isMember()){
//        int outputWidth = 30 + QFontMetrics(QFont()).boundingRect("self").width();
//        maxWidth = maxWidth>outputWidth? maxWidth:outputWidth;
//        maxHeight += 30;
//    }

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
    outputSlot()->setPos(m_bounds.width()-outputSlot()->boundingRect().width(),30);
//    if(functionObject()->isMember()){
//        m_selfSlot->setPos(3,60);
//    }
    //m_executionflowOutSlot->setPos(m_bounds.width()-15,7);
    for (int i = 0; i < m_inputParameters.size(); ++i) {
        //false to be replaces by isMember in later changes
        m_inputParameters.at(i)->setPos(3,(false?90:60)+30*i);
    }
}

QString BP_ClassInstanceNode::renderNode(BP_PlatformManager *platform)
{
    CHECK_FIRST_REFERENCE
    return platform->renderClassInstanceNode(this);
}

BP_Class *BP_ClassInstanceNode::sourceClass() const
{
    return m_sourceClass;
}

int BP_ClassInstanceNode::constructorId() const
{
    return m_constructorId;
}

QList<BP_DataSlot *> BP_ClassInstanceNode::inputParameters() const
{
    return m_inputParameters;
}

void BP_ClassInstanceNode::setSourceClass(BP_Class *sourceClass)
{
    if (m_sourceClass == sourceClass)
        return;

    m_sourceClass = sourceClass;

    //creating the variable
    BP_Variable *variable = new BP_Variable(nullptr,this);
    variable->setValue(0);
    variable->setClassName(sourceClass->name());
    variable->setSourceClass(sourceClass);
    variable->setIsMember(false);
    variable->setIsPrimitive(false);
    variable->setName("var_"+sourceClass->name()+"_"+QString::number(nodeId));
    variable->setIsArray("false");
    variable->setIsImported(false);

    setCoreObject(variable);
    setVariableObject(variable);

    outputSlot()->setReference(variable->name());

    emit sourceClassChanged(m_sourceClass);
}

void BP_ClassInstanceNode::setConstructorId(int constructorId)
{
    if (m_constructorId == constructorId && constructorId!=0)
        return;
    if(!m_sourceClass){ qDebug() << "no valid source class to set a constructor to it"; return; }
    if(constructorId>(sourceClass()->constructors().size()-1)){qDebug() << "out of bound constructor"; return;}
    m_constructorId = constructorId;

    inputParameters().clear();
    auto classConstructor = sourceClass()->constructors().at(constructorId);
    qDebug() << "the size of constructors inputs : " << classConstructor->inputs().size();
    foreach (auto parameter, classConstructor->inputs()) {
        BP_DataSlot *inputSlot = new BP_DataSlot(this);
        inputSlot->setParameterObject(parameter);
        m_inputParameters << inputSlot;
        qDebug() << "parameter found for class instance " << parameter->parameterName();
    }
    calculateBounds();
    emit constructorIdChanged(m_constructorId);
}

void BP_ClassInstanceNode::setInputParameters(QList<BP_DataSlot *> inputParameters)
{
    if (m_inputParameters == inputParameters)
        return;

    m_inputParameters = inputParameters;
    emit inputParametersChanged(m_inputParameters);
}
