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

#include <QObject>

#include <Platform/bp_platformmanager.h>

class BP_Module;
class BP_Function;

class BP_Project : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged)
    Q_PROPERTY(BP_PlatformManager* platformManager READ platformManager WRITE setPlatformManager NOTIFY platformManagerChanged)
    Q_PROPERTY(QList<BP_Module*> importedModules READ importedModules WRITE setImportedModules NOTIFY importedModulesChanged)
    Q_PROPERTY(QList<BP_Function*> importedFunctions READ importedFunctions WRITE setImportedFunctions NOTIFY importedFunctionsChanged)

    QString m_projectName;
    BP_PlatformManager* m_platformManager;
    QList<BP_Module*> m_importedModules;
    QList<BP_Function*> m_importedFunctions;

public:
    explicit BP_Project(QString projectName,QObject *parent = nullptr);

    void setupPlatform();
    void importModule(QStringList moduleHierarchy);
    void importFunction(QStringList moduleHierarchy);

    QString projectName() const;

    BP_PlatformManager* platformManager() const;

    QList<BP_Module*> importedModules() const;

    QList<BP_Function*> importedFunctions() const;

public slots:
    void setProjectName(QString projectName);

    void setPlatformManager(BP_PlatformManager* platformManager);

    void setImportedModules(QList<BP_Module*> importedModules);

    void setImportedFunctions(QList<BP_Function*> importedFunctions);

signals:

    void projectNameChanged(QString projectName);
    void platformManagerChanged(BP_PlatformManager* platformManager);
    void importedModulesChanged(QList<BP_Module*> importedModules);
    void importedFunctionsChanged(QList<BP_Function*> importedFunctions);
};

#endif // BP_PROJECT_H
