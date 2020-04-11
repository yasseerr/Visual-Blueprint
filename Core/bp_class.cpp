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
#include "bp_constructor.h"
#include "bp_function.h"
#include "bp_variable.h"

#include <QVariantMap>

BP_Class::BP_Class(QVariantMap *classMap,QObject *parent) : QObject(parent),
  m_className(""),
  m_owningModule(nullptr)
{
    m_className = classMap->value("name").toString();
    int i = 0;

    //loading constructors
    foreach (auto constructorVariant, classMap->value("constructors").toList()) {
        auto constructorMap = constructorVariant.toMap();
        BP_Constructor *new_constructor = new BP_Constructor(&constructorMap,this);
        new_constructor->setConstructorId(i);
        i++;
        m_constructors << new_constructor;
    }

    //loading variables

    foreach (auto variableVariant, classMap->value("variables").toList()) {
        auto variableMap = variableVariant.toMap();
        BP_Variable *variable = new BP_Variable(this,&variableMap);
        m_memberVariables << variable;
    }

    //loading functions

    foreach (auto functionVariant, classMap->value("variab").toList()) {
        auto functionMap = functionVariant.toMap();
        BP_Function *function_ = new BP_Function(&functionMap,this);
        m_memberFunctions << function_;
    }


}

QString BP_Class::className() const
{
    return m_className;
}

QList<BP_Variable *> BP_Class::memberVariables() const
{
    return m_memberVariables;
}

QList<BP_Function *> BP_Class::memberFunctions() const
{
    return m_memberFunctions;
}

BP_Module *BP_Class::owningModule() const
{
    return m_owningModule;
}

QStringList BP_Class::moduleHierarchy() const
{
    return m_moduleHierarchy;
}

QList<BP_Constructor *> BP_Class::constructors() const
{
    return m_constructors;
}

void BP_Class::setClassName(QString className)
{
    if (m_className == className)
        return;

    m_className = className;
    emit classNameChanged(m_className);
}

void BP_Class::setMemberVariables(QList<BP_Variable *> memberVariables)
{
    if (m_memberVariables == memberVariables)
        return;

    m_memberVariables = memberVariables;
    emit memberVariablesChanged(m_memberVariables);
}

void BP_Class::setMemberFunctions(QList<BP_Function *> memberFunctions)
{
    if (m_memberFunctions == memberFunctions)
        return;

    m_memberFunctions = memberFunctions;
    emit memberFunctionsChanged(m_memberFunctions);
}

void BP_Class::setOwningModule(BP_Module *owningModule)
{
    if (m_owningModule == owningModule)
        return;

    m_owningModule = owningModule;
    emit owningModuleChanged(m_owningModule);
}

void BP_Class::setModuleHierarchy(QStringList moduleHierarchy)
{
    if (m_moduleHierarchy == moduleHierarchy)
        return;

    m_moduleHierarchy = moduleHierarchy;
    emit moduleHierarchyChanged(m_moduleHierarchy);
}

void BP_Class::setConstructors(QList<BP_Constructor *> constructors)
{
    if (m_constructors == constructors)
        return;

    m_constructors = constructors;
    emit constructorsChanged(m_constructors);
}
