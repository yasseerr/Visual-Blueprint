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

class BP_Project : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged)
    Q_PROPERTY(BP_PlatformManager* platformManager READ platformManager WRITE setPlatformManager NOTIFY platformManagerChanged)
    QString m_projectName;

    BP_PlatformManager* m_platformManager;

public:
    explicit BP_Project(QString projectName,QObject *parent = nullptr);

    void setupPlatform();

    QString projectName() const;

    BP_PlatformManager* platformManager() const;

public slots:
    void setProjectName(QString projectName);

    void setPlatformManager(BP_PlatformManager* platformManager);

signals:

    void projectNameChanged(QString projectName);
    void platformManagerChanged(BP_PlatformManager* platformManager);
};

#endif // BP_PROJECT_H
