/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_function.h"
#include "bp_module.h"
#include "bp_project.h"
#include "bp_variable.h"

#include <Platform/Python/bp_pythonmanager.h>

#include <QDebug>
#include <QVariantMap>

BP_Project::BP_Project(QString projectName,QObject *parent) : QObject(parent),
    m_projectName(projectName)
{

}

void BP_Project::setupPlatform()
{
    m_platformManager = new BP_PythonManager(this);
}

void BP_Project::importModule(QStringList moduleHierarchy)
{
    QVariantMap moduleMap = m_platformManager->importModule(moduleHierarchy);
//    qDebug()<< "module imported :" << endl << moduleMap;
    BP_Module *importedModule = new BP_Module(moduleMap.value("name").toString(),this);
    qDebug() << "module Name : " << importedModule->name();
    m_importedModules.append(importedModule);
}

void BP_Project::importFunction(QStringList moduleHierarchy)
{
    QVariantMap functionMap = m_platformManager->importFunction(moduleHierarchy);
    qDebug()<< "module imported :" << endl << functionMap;
    BP_Function *importedFunction = new BP_Function(functionMap.value("name").toString(),this);
    qDebug() << "Function Name : " << importedFunction->functionName();
    m_importedFunctions.append(importedFunction);
}

void BP_Project::importVariable(QStringList moduleHierarchy)
{
    QVariantMap variableMap = m_platformManager->importVariable(moduleHierarchy);
    qDebug()<< "variable imported :" << endl << variableMap;
    BP_Variable *importedVariable = new BP_Variable(this);
    importedVariable->setVariableName(variableMap.value("name").toString());
    qDebug() << "Variable Name : " << importedVariable->variableName();
    m_importedVariables.append(importedVariable);
}

void BP_Project::importClass(QStringList moduleHierarchy)
{

}

QString BP_Project::projectName() const
{
    return m_projectName;
}

BP_PlatformManager *BP_Project::platformManager() const
{
    return m_platformManager;
}

QList<BP_Module *> BP_Project::importedModules() const
{
    return m_importedModules;
}

QList<BP_Function *> BP_Project::importedFunctions() const
{
    return m_importedFunctions;
}

QList<BP_Variable *> BP_Project::importedVariables() const
{
    return m_importedVariables;
}

void BP_Project::setProjectName(QString projectName)
{
    if (m_projectName == projectName)
        return;

    m_projectName = projectName;
    emit projectNameChanged(m_projectName);
}

void BP_Project::setPlatformManager(BP_PlatformManager *platformManager)
{
    if (m_platformManager == platformManager)
        return;

    m_platformManager = platformManager;
    emit platformManagerChanged(m_platformManager);
}

void BP_Project::setImportedModules(QList<BP_Module *> importedModules)
{
    if (m_importedModules == importedModules)
        return;

    m_importedModules = importedModules;
    emit importedModulesChanged(m_importedModules);
}

void BP_Project::setImportedFunctions(QList<BP_Function *> importedFunctions)
{
    if (m_importedFunctions == importedFunctions)
        return;

    m_importedFunctions = importedFunctions;
    emit importedFunctionsChanged(m_importedFunctions);
}

void BP_Project::setImportedVariables(QList<BP_Variable *> importedVariables)
{
    if (m_importedVariables == importedVariables)
        return;

    m_importedVariables = importedVariables;
    emit importedVariablesChanged(m_importedVariables);
}
