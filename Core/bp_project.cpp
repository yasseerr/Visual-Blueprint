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
#include "bp_project.h"
#include "bp_variable.h"

#include <Platform/Python/bp_pythonmanager.h>

#include <QDebug>
#include <QFileDialog>
#include <QJsonDocument>
#include <QVariantMap>
#include <bp_utils.h>

#include <Graph/bp_graphview.h>
#include <Graph/bp_node.h>
#include <Graph/bp_slot.h>


BP_Project::BP_Project(QString projectName,QObject *parent) : QObject(parent),
    m_projectName(projectName)
{
    setEntryGraph(new BP_GraphView());
}

void BP_Project::setupPlatform()
{
    //TODO specify the platform in the parameters
    m_platformManager = new BP_PythonManager(this);
    m_platformManager->loadBuiltins(this);
}

void BP_Project::importModule(QStringList moduleHierarchy)
{
    QVariantMap moduleMap = m_platformManager->importModule(moduleHierarchy);
//    qDebug()<< "module imported :" << endl << moduleMap;
    BP_Module *importedModule = new BP_Module(&moduleMap,this);
    importedModule->setImportHiearchy(moduleHierarchy);
    qDebug() << "module Name : " << importedModule->name();
    m_importedModules.append(importedModule);

    emit importedItemsAdded(importedModule);
}

void BP_Project::importFunction(QStringList moduleHierarchy)
{
    QVariantMap functionMap = m_platformManager->importFunction(moduleHierarchy);
    qDebug()<< "module imported :" << endl << functionMap;
    BP_Function *importedFunction = new BP_Function(&functionMap,this);
    importedFunction->setImportHiearchy(moduleHierarchy);
    qDebug() << "Function Name : " << importedFunction->name();
    m_importedFunctions.append(importedFunction);

    emit importedItemsAdded(importedFunction);
}

void BP_Project::importVariable(QStringList moduleHierarchy)
{
    QVariantMap variableMap = m_platformManager->importVariable(moduleHierarchy);
    qDebug()<< "variable imported :" << endl << variableMap;
    BP_Variable *importedVariable = new BP_Variable(&variableMap,this,&moduleHierarchy);
    qDebug() << "Variable Value : " << importedVariable->value();
    m_importedVariables.append(importedVariable);

    emit importedItemsAdded(importedVariable);

}

void BP_Project::importClass(QStringList moduleHierarchy)
{
    QVariantMap classMap = m_platformManager->importClass(moduleHierarchy);
    qDebug()<< "class imported :" << endl << classMap;
    BP_Class *importedClass = new BP_Class(&classMap,this);
    importedClass->setImportHiearchy(moduleHierarchy);
    importedClass->setName(classMap.value("name").toString());
    qDebug() << "class Name : " << importedClass->name();
    //TODO add a new function when appending to update the project maybe project signal
    m_importedClasses.append(importedClass);

    emit importedItemsAdded(importedClass);
}

void BP_Project::addMemberVariable(BP_Variable *newVariable)
{
    m_memberVariables << newVariable;
}

void BP_Project::addBuiltin(BP_CoreObject *builtInObj)
{
    m_builtins << builtInObj;
}

QVariant BP_Project::toVariantBP()
{
    QVariantMap retMap;
    retMap["name"] = m_projectName;

    //TODO save the used platform
    //retMap["platform"] = "python";

    //save the entry graph
    retMap["entryGraph"] = m_entryGraph->toVariantBP();
    retMap["nodesCount"] = BP_Node::nodeCount;
    retMap["slotsCount"] = BP_Slot::slotCount;

    //TODO save the other graphs

    //save the imports
    //models
    QVariantList importedModulesVariantList;
    foreach (auto module, m_importedModules) {
        importedModulesVariantList << module->toVariantBP();
    }
    QVariantList importedFunctionsVariantList;
    foreach (auto f, m_importedFunctions) {
        importedFunctionsVariantList << f->toVariantBP();
    }
    QVariantList importedClassesVariantList;
    foreach (auto c, m_importedClasses) {
        importedClassesVariantList << c->toVariantBP();
    }
    QVariantList importedVariablesVariantList;
    foreach (auto v, m_importedVariables) {
        importedVariablesVariantList << v->toVariantBP();
    }

    retMap["importedModules"] = importedModulesVariantList;
    retMap["importedFunctions"] = importedFunctionsVariantList;
    retMap["importedClasses"] = importedClassesVariantList;
    retMap["importedVariables"] = importedVariablesVariantList;

    //save the members
    //member variable
    QVariantList memberVariablesVariantList;
    foreach (auto v, m_memberVariables) {
        importedVariablesVariantList << v->getVariableAsVariant();
    }

    retMap["memberVariables"] = memberVariablesVariantList;


    return retMap;
}

void BP_Project::saveProject()
{
//    QString fileName = QFileDialog::getSaveFileName(nullptr,"saving the project",QString(),"*.vbl");
//    if(fileName == ""){
//        BP_Utils::log("no valid file was selected");
//        return;
//    }
    //qDebug() << "saving project in file : " << fileName;
    QJsonDocument doc = QJsonDocument::fromVariant(this->toVariantBP());
    QFile destinationFile("C:/Users/HP/Desktop/newFile.vbl");
    destinationFile.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream ds(&destinationFile);
    ds << doc.toJson();
    destinationFile.close();
}

void BP_Project::loadProject(QVariant projectVariant)
{
    //TODO use a new project instead
    //BP_Project *loadedProject = new BP_Project("")
    QVariantMap projectMap = projectVariant.toMap();
    BP_Project *loadedProject = this;
    loadedProject->setProjectName(projectMap["name"].toString());
    qDebug() << projectVariant.toString();

    //TODO setup the platform for the type of project
    //TODO load the imports depending on the platform

    //load imported functions/modules/...
    QVariantList toImport;
    toImport << projectMap.value("importedModules").toList()
             << projectMap.value("importedFunctions").toList()
             << projectMap.value("importedClasses").toList()
             << projectMap.value("importedVariables").toList();
    foreach (auto m, toImport) {
        auto moduleHierarchy = m.toMap()["importHierarcht"].toStringList();
        qDebug()<< "loading module "<< moduleHierarchy;
        //TODO add the variables to the variablesMap

        //platformManager()->importModule(moduleHierarchy);
        BP_Utils::instance()->importsModel->importFromHieararchy(moduleHierarchy);
    }
    
    //TODO load members

    //load the entry graph
    loadedProject->entryGraph()->fromVariantBP(projectMap["entryGraph"]);
    //TODO check if it is the greater value
    BP_Node::nodeCount = projectMap["nodesCount"].toInt();
    BP_Slot::slotCount = projectMap["slotsCount"].toInt();
    qDebug() << "the loading says that the number of nodes is " << BP_Node::nodeCount << BP_Slot::slotCount;

    //TODO load all the graphs

}

QString BP_Project::projectName() const
{
    return m_projectName;
}

BP_PlatformManager *BP_Project::platformManager() const
{
    return m_platformManager;
}

QList<BP_Module*> BP_Project::importedModules() const
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

QList<BP_Class *> BP_Project::importedClasses() const
{
    return m_importedClasses;
}

QList<BP_Variable *> BP_Project::memberVariables() const
{
    return m_memberVariables;
}

BP_GraphView *BP_Project::entryGraph() const
{
    return m_entryGraph;
}

QList<BP_GraphView *> BP_Project::functionsGraphs() const
{
    return m_functionsGraphs;
}

QList<BP_CoreObject *> BP_Project::builtins() const
{
    return m_builtins;
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

void BP_Project::setImportedModules(QList<BP_Module*> importedModules)
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

void BP_Project::setImportedClasses(QList<BP_Class *> importedClasses)
{
    if (m_importedClasses == importedClasses)
        return;

    m_importedClasses = importedClasses;
    emit importedClassesChanged(m_importedClasses);
}

void BP_Project::setMemberVariables(QList<BP_Variable *> memberVariables)
{
    if (m_memberVariables == memberVariables)
        return;

    m_memberVariables = memberVariables;
    emit memberVariablesChanged(m_memberVariables);
}

void BP_Project::setEntryGraph(BP_GraphView *entryGraph)
{
    if (m_entryGraph == entryGraph)
        return;

    m_entryGraph = entryGraph;
    emit entryGraphChanged(m_entryGraph);
}

void BP_Project::setFunctionsGraphs(QList<BP_GraphView *> functionsGraphs)
{
    if (m_functionsGraphs == functionsGraphs)
        return;

    m_functionsGraphs = functionsGraphs;
    emit functionsGraphsChanged(m_functionsGraphs);
}

void BP_Project::setBuiltins(QList<BP_CoreObject *> builtins)
{
    if (m_builtins == builtins)
        return;

    m_builtins = builtins;
    emit builtinsChanged(m_builtins);
}
