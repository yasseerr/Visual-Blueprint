/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_project.h"

#include <Platform/Python/bp_pythonmanager.h>

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
    QVariantMap
}

QString BP_Project::projectName() const
{
    return m_projectName;
}

BP_PlatformManager *BP_Project::platformManager() const
{
    return m_platformManager;
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
