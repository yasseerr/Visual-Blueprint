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
#include "bp_variable.h"

BP_Variable::BP_Variable(QVariantMap *variableMap,QObject *parent,QStringList *moduleHiearchy) : BP_CoreObject(parent),
   m_isPrimitive(false),
   m_isArray(false),
   m_isMember(false),
   m_owningClass(nullptr),
   m_owningModule(nullptr),
   m_className("")
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
