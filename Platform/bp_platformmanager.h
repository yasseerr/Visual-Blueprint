/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                    *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_PLATFORMMANAGER_H
#define BP_PLATFORMMANAGER_H

#include <QObject>
#include <QProcess>

class BP_PlatformManager : public QObject
{
    Q_OBJECT
public:
    explicit BP_PlatformManager(QObject *parent = nullptr);

    //classes to implement according to Framwork/languages
    virtual QStringList listGlobalModules() = 0;
    virtual QList<QPair<QString,QString>> inspectModuleByName(QStringList moduleHierarchy) = 0;
    virtual QVariantMap importModule(QStringList moduleHiearchy) = 0;

public slots:
    //slots for the manager process
    virtual void standardOutputReady() = 0;
    virtual void errorOutputReady() = 0;

public:
    QString m_language = "";
    QString m_framwork= "";
    QString m_compilerPath= "";
    QString m_managerFile = "";

    QProcess m_managerProcess;




};

#endif // BP_PLATFORMMANAGER_H
