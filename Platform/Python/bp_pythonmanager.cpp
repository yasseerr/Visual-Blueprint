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

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>

BP_PythonManager::BP_PythonManager(QObject *parent):BP_PlatformManager(parent)
{
    m_language = "python";
    m_framwork = "standard";
    m_compilerPath = "C:/Python38/python.exe";
    m_managerFile = "./Platform/Python/python_manager.py";
//    QObject::connect(&m_managerProcess,&QProcess::readyReadStandardOutput,this,&BP_PythonManager::standardOutputReady);
//    QObject::connect(&m_managerProcess,&QProcess::readyReadStandardError,this,&BP_PythonManager::errorOutputReady);
}

QStringList BP_PythonManager::listGlobalModules()
{
    QStringList returnList;

    m_managerProcess.setProgram(m_compilerPath);
    m_managerProcess.setArguments(QStringList() << m_managerFile << "listGM");
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    QJsonArray listJson = QJsonDocument::fromJson(listRawData).array();
    foreach (auto item, listJson) {
        returnList << item.toString();
        qDebug() << item.toString();
    }
    return returnList;
}

void BP_PythonManager::standardOutputReady()
{
    qDebug() << "Data Ready : " << m_managerProcess.readAllStandardOutput();
}

void BP_PythonManager::errorOutputReady()
{
    qDebug() << "Error Ready : " << m_managerProcess.readAllStandardError();
}
