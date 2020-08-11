/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_variablenode.h"

#include <Graph/Slots/bp_dataslot.h>

#include <QDebug>
#include <bp_utils.h>
#include <qpainter.h>

#include <Core/bp_parameter.h>
#include <Core/bp_variable.h>

#include <Graph/bp_graphutils.h>


RegisterNodeType(BP_VariableNode)
//int BP_VariableNode::nodeTypeID = BP_VariableNode::setupNodeType(X::staticMetaObject);

BP_VariableNode::BP_VariableNode():BP_Node(),m_variableObject(nullptr),m_outputSlot(new BP_DataSlot(this))
{
    m_outputSlot->setParentItem(this);
    m_outputSlot->setIsOutput(true);
    m_outputSlot->setShowName(false);
}

QVariant BP_VariableNode::toVariantBP()
{
    //TODO do not save the variable object when the variable is a project member
    QVariantMap retMap = BP_Node::toVariantBP().toMap();
    retMap["type"] = getNodeTypeString();
    retMap["variableObject"] =m_variableObject&& !m_variableObject->isProjectMember()?variableObject()->toVariantBP():false;
    retMap["variableValue"] = m_variableObject&& !m_variableObject->isProjectMember()?variableObject()->value():false;
    retMap["outputSlot"] = m_outputSlot->toVariantBP();
    retMap["isProjectMember"] = m_variableObject->isProjectMember();
    retMap["projectMemberName"] =  m_variableObject->isProjectMember()?m_variableObject->name():"";
    return retMap;
}

void BP_VariableNode::fromVariant(QVariant var)
{
    BP_Node::fromVariant(var);
    auto varMap = var.toMap();
    if(coreObject() && (coreObject()->isImported()|| coreObject()->isProjectMember())){
        setVariableObject(qobject_cast<BP_Variable*>(coreObject()));
    }
    //Text that the variable exist for nodes like ClassInstance where it is nullptr
    if(variableObject() && !variableObject()->isImported()){
        m_variableObject->setValue(varMap["variableValue"]);

        qDebug() << "about to include the new value of "<< m_variableObject->value();
        emit updateDisplay();
    }
    m_outputSlot->fromVariant(varMap["outputSlot"]);


}

void BP_VariableNode::updateSlotsBranches(BP_Slot *slot)
{
    if(slot == m_outputSlot && m_variableObject && m_variableObject->isProjectMember()){
        foreach (auto branch, m_outputSlot->frameBranches()) {
            m_variableObject->m_connectedBranches.insert(branch);
        }
    }
}

void BP_VariableNode::calculateBounds()
{
    BP_Node::calculateBounds();
    m_bounds.setHeight(30);
    m_bounds.setWidth(m_bounds.width()+30);
    m_outputSlot->setPos(m_outputSlot->mapFromParent(m_bounds.width()-17,-7));
}


void BP_VariableNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //BP_Node::paint(painter,option,widget);
    //painter->setPen(Qt::);
    painter->setBrush(Qt::GlobalColor::green);
    painter->drawRoundedRect(boundingRect(),2,2);
    painter->drawText(5,7,m_variableObject->name());
}

BP_Variable *BP_VariableNode::variableObject() const
{
    return m_variableObject;
}

BP_DataSlot *BP_VariableNode::outputSlot() const
{
    return m_outputSlot;
}

QString BP_VariableNode::getNodeTypeString()
{
    return "Variable";
}

QString BP_VariableNode::renderNode(BP_PlatformManager *platform)
{
    //TODO change the python comment
    return "#calling a member variable";
}



void BP_VariableNode::setVariableObject(BP_Variable *variableObject)
{
    if (m_variableObject == variableObject)
        return;
    m_variableObject = variableObject;

    BP_Parameter *param = new BP_Parameter(m_outputSlot);
    m_variableObject->getAsParameter(param);
    m_outputSlot->setParameterObject(param);
    m_outputSlot->setReference((m_variableObject->isProjectMember()?"self.":"")+variableObject->name());

    emit variableObjectChanged(m_variableObject);
}

void BP_VariableNode::setOutputSlot(BP_DataSlot *outputSlot)
{
    if (m_outputSlot == outputSlot)
        return;

    m_outputSlot = outputSlot;
    emit outputSlotChanged(m_outputSlot);
}

