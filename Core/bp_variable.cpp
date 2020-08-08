/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_class.h"
#include "bp_module.h"
#include "bp_parameter.h"
#include "bp_variable.h"

#include <Graph/bp_node.h>

#include <Graph/Nodes/bp_intnode.h>
#include <Graph/Nodes/bp_variablenode.h>

BP_Variable::BP_Variable(QVariantMap *variableMap,QObject *parent,QStringList *moduleHiearchy) : BP_CoreObject(parent),
   m_isPrimitive(false),
   m_isArray(false),
   m_isMember(false),
   m_owningClass(nullptr),
   m_owningModule(nullptr),
   m_className(""),
   m_sourceClass(nullptr),
   m_isProjectMember(false)
{
    //TODO add the class name and the class module
    //TODO check if the variable class is already imported
    if(variableMap != nullptr){
        setName(variableMap->value("name").toString());
        m_isPrimitive  = variableMap->value("isPrimitive").toBool();
        m_value = variableMap->value("value");
        m_className = variableMap->value("className").toString();

    }

    if(moduleHiearchy != nullptr)
        setImportHiearchy(*moduleHiearchy);

}

QVariantMap BP_Variable::getDefaultVariantMap()
{
    QVariantMap retMap;
    retMap.insert("name","NewVariable");
    retMap.insert("isPrimitive",true);
    retMap.insert("value",0);
    retMap.insert("className","unknown");
    return retMap;
}

void BP_Variable::getAsParameter(BP_Parameter *param)
{
    if(!param) return;
    param->setKind(BP_Parameter::Kind::POSITIONAL_OR_KEYWORD);
    param->setDefualtValue(this);
    param->setParameterName(this->name());
    //TODO create a class map and assign the class to the
    //parameter throught the name
    //param->setParameterClass()

}

QVariantMap BP_Variable::getVariableAsVariant()
{
    QVariantMap retMap;
    retMap.insert("name",name());
    retMap.insert("isPrimitive",m_isPrimitive);
    retMap.insert("value",value());
    retMap.insert("sourceClass",m_sourceClass?sourceClass()->toVariantBP():false);
    return retMap;
}


bool BP_Variable::isPrimitive() const
{
    return m_isPrimitive;
}

bool BP_Variable::isArray() const
{
    return m_isArray;
}

bool BP_Variable::isMember() const
{
    return m_isMember;
}

QVariant BP_Variable::value() const
{
    return m_value;
}

BP_Class *BP_Variable::owningClass() const
{
    return m_owningClass;
}

BP_Module *BP_Variable::owningModule() const
{
    return m_owningModule;
}


QString BP_Variable::className() const
{
    return m_className;
}

QStringList BP_Variable::classModuleHiearchy() const
{
    return m_classModuleHiearchy;
}


void BP_Variable::setIsPrimitive(bool isPrimitive)
{
    if (m_isPrimitive == isPrimitive)
        return;

    m_isPrimitive = isPrimitive;
    emit isPrimitiveChanged(m_isPrimitive);
}

void BP_Variable::setIsArray(bool isArray)
{
    if (m_isArray == isArray)
        return;

    m_isArray = isArray;
    emit isArrayChanged(m_isArray);
}

void BP_Variable::setIsMember(bool isMember)
{
    if (m_isMember == isMember)
        return;

    m_isMember = isMember;
    emit isMemberChanged(m_isMember);
}

void BP_Variable::setValue(QVariant value)
{
    if (m_value == value)
        return;

    m_value = value;
    emit valueChanged(m_value);
}

void BP_Variable::setOwningClass(BP_Class *owningClass)
{
    if (m_owningClass == owningClass)
        return;

    m_owningClass = owningClass;
    emit owningClassChanged(m_owningClass);
}

void BP_Variable::setOwningModule(BP_Module *owningModule)
{
    if (m_owningModule == owningModule)
        return;

    m_owningModule = owningModule;
    emit owningModuleChanged(m_owningModule);
}


void BP_Variable::setClassName(QString className)
{
    if (m_className == className)
        return;

    m_className = className;
    emit classNameChanged(m_className);
}

void BP_Variable::setClassModuleHiearchy(QStringList classModuleHiearchy)
{
    if (m_classModuleHiearchy == classModuleHiearchy)
        return;

    m_classModuleHiearchy = classModuleHiearchy;
    emit classModuleHiearchyChanged(m_classModuleHiearchy);
}

void BP_Variable::setSourceClass(BP_Class *sourceClass)
{
    if (m_sourceClass == sourceClass)
        return;

    m_sourceClass = sourceClass;
    emit sourceClassChanged(m_sourceClass);
}

void BP_Variable::setIsProjectMember(bool isProjectMember)
{
    if (m_isProjectMember == isProjectMember)
        return;

    m_isProjectMember = isProjectMember;
    emit isProjectMemberChanged(m_isProjectMember);
}

BP_Node *BP_Variable::createNodeForObject(QObject *parent)
{
    //BP_VariableNode *variableNode = new BP_VariableNode();
    BP_VariableNode *variableNode = new BP_VariableNode();
    variableNode->setParent(parent);
    variableNode->setCoreObject(this);
    variableNode->setVariableObject(this);
    return  variableNode;
}

BP_Class *BP_Variable::sourceClass() const
{
    return m_sourceClass;
}

bool BP_Variable::isProjectMember() const
{
    return m_isProjectMember;
}
