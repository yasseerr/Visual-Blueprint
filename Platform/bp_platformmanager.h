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

class BP_PlatformManager : public QObject
{
    Q_OBJECT
public:
    explicit BP_PlatformManager(QObject *parent = nullptr);

    //classes to implement according to Framwork/languages
    virtual QStringList listGlobalModules() = 0;

    QString m_language = "";
    QString m_framwork= "";



};

#endif // BP_PLATFORMMANAGER_H
