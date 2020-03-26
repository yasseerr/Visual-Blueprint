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

class BP_Project : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged)
    Q_PROPERTY(BP_PlatformManager* platformManager READ platformManager WRITE setPlatformManager NOTIFY platformManagerChanged)
    Q_PROPERTY(QList<BP_Module*> importedModules READ importedModules WRITE setImportedModules NOTIFY importedModulesChanged)

    QString m_projectName;
    BP_PlatformManager* m_platformManager;
    QList<BP_Module*> m_importedModules;

public:
    explicit BP_Project(QString projectName,QObject *parent = nullptr);

    void setupPlatform();
    void importModule(QStringList moduleHierarchy);

    QString projectName() const;

    BP_PlatformManager* platformManager() const;

    QList<BP_Module*> importedModules() const;

public slots:
    void setProjectName(QString projectName);

    void setPlatformManager(BP_PlatformManager* platformManager);

    void setImportedModules(QList<BP_Module*> importedModules);

signals:

    void projectNameChanged(QString projectName);
    void platformManagerChanged(BP_PlatformManager* platformManager);
    void importedModulesChanged(QList<BP_Module*> importedModules);
};

#endif // BP_PROJECT_H
