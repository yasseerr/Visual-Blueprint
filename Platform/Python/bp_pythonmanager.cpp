/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_pythonmanager.h"

BP_PythonManager::BP_PythonManager(QObject *parent):BP_PlatformManager(parent)
{
    m_language = "python";
    m_framwork = "standard";

}

QStringList BP_PythonManager::listGlobalModules()
{
    QStringList returnList;




    return returnList;
}
