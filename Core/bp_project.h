/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_PROJECT_H
#define BP_PROJECT_H

#include "bp_class.h"
#include "bp_coreobject.h"
#include "bp_function.h"
#include "bp_module.h"
#include "bp_variable.h"

#include <QObject>

#include <Platform/bp_platformmanager.h>

//class BP_Module;
//class BP_Function;
//class BP_Variable;
//class BP_Class;
class BP_GraphView;

//registring types to be recognised by Grantlee
Q_DECLARE_METATYPE(QList<BP_Module*>)
Q_DECLARE_METATYPE(QList<BP_Class*>)
Q_DECLARE_METATYPE(QList<BP_Function*>)
Q_DECLARE_METATYPE(QList<BP_Variable*>)
class BP_Project : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged)
    Q_PROPERTY(BP_PlatformManager* platformManager READ platformManager WRITE setPlatformManager NOTIFY platformManagerChanged)
    Q_PROPERTY(QList<BP_Module*> importedModules READ importedModules WRITE setImportedModules NOTIFY importedModulesChanged)
    Q_PROPERTY(QList<BP_Function*> importedFunctions READ importedFunctions WRITE setImportedFunctions NOTIFY importedFunctionsChanged)
    Q_PROPERTY(QList<BP_Variable*> importedVariables READ importedVariables WRITE setImportedVariables NOTIFY importedVariablesChanged)
    Q_PROPERTY(QList<BP_Class*> importedClasses READ importedClasses WRITE setImportedClasses NOTIFY importedClassesChanged)
    Q_PROPERTY(QList<BP_CoreObject*> builtins READ builtins WRITE setBuiltins NOTIFY builtinsChanged)

    Q_PROPERTY(QList<BP_Variable*> memberVariables READ memberVariables WRITE setMemberVariables NOTIFY memberVariablesChanged)
    Q_PROPERTY(BP_GraphView* entryGraph READ entryGraph WRITE setEntryGraph NOTIFY entryGraphChanged)
    Q_PROPERTY(QList<BP_GraphView*> functionsGraphs READ functionsGraphs WRITE setFunctionsGraphs NOTIFY functionsGraphsChanged)

    QString m_projectName;
    BP_PlatformManager* m_platformManager;
    QList<BP_Module*> m_importedModules;
    QList<BP_Function*> m_importedFunctions;
    QList<BP_Variable*> m_importedVariables;
    QList<BP_Class*> m_importedClasses;
    QList<BP_Variable*> m_memberVariables;
    BP_GraphView* m_entryGraph;
    QList<BP_GraphView*> m_functionsGraphs;    
    QList<BP_CoreObject*> m_builtins;

public:
    explicit BP_Project(QString projectName,QObject *parent = nullptr);

    void setupPlatform();
    void importModule(QStringList moduleHierarchy);
    void importFunction(QStringList moduleHierarchy);
    void importVariable(QStringList moduleHierarchy);
    void importClass(QStringList moduleHierarchy);

    void addMemberVariable(BP_Variable *newVariable);
    void addBuiltin(BP_CoreObject *builtInObj);

    QString projectName() const;

    BP_PlatformManager* platformManager() const;

    QList<BP_Module*> importedModules() const;

    QList<BP_Function*> importedFunctions() const;

    QList<BP_Variable*> importedVariables() const;

    QList<BP_Class*> importedClasses() const;

    QList<BP_Variable*> memberVariables() const;

    BP_GraphView* entryGraph() const;

    QList<BP_GraphView*> functionsGraphs() const;

    QList<BP_CoreObject*> builtins() const;

public slots:
    void setProjectName(QString projectName);

    void setPlatformManager(BP_PlatformManager* platformManager);

    void setImportedModules(QList<BP_Module*> importedModules);

    void setImportedFunctions(QList<BP_Function*> importedFunctions);

    void setImportedVariables(QList<BP_Variable*> importedVariables);

    void setImportedClasses(QList<BP_Class*> importedClasses);

    void setMemberVariables(QList<BP_Variable*> memberVariables);

    void setEntryGraph(BP_GraphView* entryGraph);

    void setFunctionsGraphs(QList<BP_GraphView*> functionsGraphs);

    void setBuiltins(QList<BP_CoreObject*> builtins);

signals:
    void importedItemsAdded(BP_CoreObject *newImportedObj);

    void projectNameChanged(QString projectName);
    void platformManagerChanged(BP_PlatformManager* platformManager);
    void importedModulesChanged(QList<BP_Module*> importedModules);
    void importedFunctionsChanged(QList<BP_Function*> importedFunctions);
    void importedVariablesChanged(QList<BP_Variable*> importedVariables);
    void importedClassesChanged(QList<BP_Class*> importedClasses);
    void memberVariablesChanged(QList<BP_Variable*> memberVariables);
    void entryGraphChanged(BP_GraphView* entryGraph);
    void functionsGraphsChanged(QList<BP_GraphView*> functionsGraphs);
    void builtinsChanged(QList<BP_CoreObject*> builtins);
};

#endif // BP_PROJECT_H
