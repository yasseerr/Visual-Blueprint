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
#include "bp_function.h"
#include "bp_module.h"
#include "bp_variable.h"

#include <QVariantMap>

BP_Module::BP_Module(QVariantMap *moduleVariant,QObject *parent) : BP_CoreObject(parent),
  m_alias("")
{
    if(moduleVariant != nullptr){
        setName(moduleVariant->value("name").toString());

        //loading functions
        foreach (auto functionVariant, moduleVariant->value("functions").toList()) {
            QVariantMap functionMap = functionVariant.toMap();
            BP_Function *moduleFunction = new BP_Function(&functionMap,this);
            moduleFunction->setOwningModule(this);

            m_functions << moduleFunction;
        }

        //loading classes
        foreach (auto classVariant, moduleVariant->value("classes").toList()) {
            QVariantMap classMap = classVariant.toMap();
            BP_Class *moduleClass = new BP_Class(&classMap,this);
            moduleClass->setOwningModule(this);

            m_classes << moduleClass;
        }

        //loading variables
        foreach (auto varVariant, moduleVariant->value("variables").toList()) {
            QVariantMap varMap = varVariant.toMap();
            BP_Variable *moduleVar = new BP_Variable(&varMap,this);
            moduleVar->setOwningModule(this);
            m_moduleValues << moduleVar;
        }
    }

}



QList<BP_Function *> BP_Module::functions() const
{
    return m_functions;
}

QList<BP_Class *> BP_Module::classes() const
{
    return m_classes;
}

QList<BP_Variable *> BP_Module::moduleValues() const
{
    return m_moduleValues;
}

QString BP_Module::alias() const
{
    return m_alias;
}


void BP_Module::setFunctions(QList<BP_Function *> functions)
{
    if (m_functions == functions)
        return;

    m_functions = functions;
    emit functionsChanged(m_functions);
}

void BP_Module::setClasses(QList<BP_Class *> classes)
{
    if (m_classes == classes)
        return;

    m_classes = classes;
    emit classesChanged(m_classes);
}

void BP_Module::setModuleValues(QList<BP_Variable *> moduleValues)
{
    if (m_moduleValues == moduleValues)
        return;

    m_moduleValues = moduleValues;
    emit moduleValuesChanged(m_moduleValues);
}

void BP_Module::setAlias(QString alias)
{
    if (m_alias == alias)
        return;

    m_alias = alias;
    emit aliasChanged(m_alias);
}


