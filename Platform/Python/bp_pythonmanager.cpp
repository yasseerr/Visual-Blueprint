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
#include <QJsonObject>

#include <Core/bp_project.h>

#include <Graph/bp_graphview.h>
#include <Graph/bp_node.h>

#include <Graph/Nodes/bp_eventnode.h>
#include <Graph/Nodes/bp_functionnode.h>

BP_PythonManager::BP_PythonManager(QObject *parent):BP_PlatformManager(parent)
{
    m_language = "python";
    m_framwork = "standard";
    m_compilerPath = "F:/Program Files/WPy64-3720/python-3.7.2.amd64/python.exe";
    m_managerFile = "./Platform/Python/python_manager.py";
    m_managerProcess.setProgram(m_compilerPath);
//    QObject::connect(&m_managerProcess,&QProcess::readyReadStandardOutput,this,&BP_PythonManager::standardOutputReady);
//    QObject::connect(&m_managerProcess,&QProcess::readyReadStandardError,this,&BP_PythonManager::errorOutputReady);
}

QStringList BP_PythonManager::listGlobalModules()
{
    QStringList returnList;

    m_managerProcess.setArguments(QStringList() << m_managerFile << "listGM");
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    QJsonArray listJson = QJsonDocument::fromJson(listRawData).array();
    foreach (auto item, listJson) {
        returnList << item.toString();
        //qDebug() << item.toString();
    }
    return returnList;
}

QList<QPair<QString, QString>> BP_PythonManager::inspectModuleByName(QStringList moduleHierachy)
{
    QList<QPair<QString,QString>> retList;
    m_managerProcess.setArguments(QStringList() << m_managerFile << "inspectModule" << moduleHierachy);
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    //qDebug() << listRawData;
    qDebug() << m_managerProcess.readAllStandardError();
    QJsonArray listJson = QJsonDocument::fromJson(listRawData).array();
    foreach (auto item, listJson) {
        QPair<QString,QString> importInfo;
        importInfo.first = item.toObject().value("name").toString();
        importInfo.second = item.toObject().value("type").toString();
        retList << importInfo;
        //qDebug() << retList;
    }
    return retList;
}

QVariantMap BP_PythonManager::importModule(QStringList moduleHiearchy)
{
    m_managerProcess.setArguments(QStringList() << m_managerFile << "importModule" << moduleHiearchy);
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    //qDebug() << listRawData;
    qDebug() << m_managerProcess.readAllStandardError();
    QJsonObject jsonObject = QJsonDocument::fromJson(listRawData).object();
    return jsonObject.toVariantMap();
}

QVariantMap BP_PythonManager::importFunction(QStringList moduleHiearchy)
{
    m_managerProcess.setArguments(QStringList() << m_managerFile << "importFunction" << moduleHiearchy);
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    //qDebug() << listRawData;
    qDebug() << m_managerProcess.readAllStandardError();
    QJsonObject jsonObject = QJsonDocument::fromJson(listRawData).object();
    return jsonObject.toVariantMap();
}

QVariantMap BP_PythonManager::importVariable(QStringList moduleHiearchy)
{
    qDebug() << "Variable Module Hiearchy > " << moduleHiearchy;
    m_managerProcess.setArguments(QStringList() << m_managerFile << "importVariable" << moduleHiearchy);
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    //qDebug() << listRawData;
    qDebug() << m_managerProcess.readAllStandardError();
    QJsonObject jsonObject = QJsonDocument::fromJson(listRawData).object();
    return jsonObject.toVariantMap();
}

QVariantMap BP_PythonManager::importClass(QStringList moduleHiearchy)
{
    qDebug() << "Class Module Hiearchy > " << moduleHiearchy;
    m_managerProcess.setArguments(QStringList() << m_managerFile << "importClass" << moduleHiearchy);
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    //qDebug() << listRawData;
    qDebug() << m_managerProcess.readAllStandardError();
    QJsonObject jsonObject = QJsonDocument::fromJson(listRawData).object();
    return jsonObject.toVariantMap();
}

void BP_PythonManager::compileProject(BP_Project *project)
{
    //rendering the imports
    auto projectTemplate = grantleeEngine->loadByName("Python/templates/project.j2");
    QVariantHash mapping ;
    mapping.insert("project",QVariant::fromValue(project));
    //filing the init function with entryGraph content
    QStringList mainCodeList;
    BP_Node *currentCompilationNode = project->entryGraph()->entryNode();
    while (currentCompilationNode) {
        QString nodeRenderedCode = currentCompilationNode->renderNode(this);
        mainCodeList << nodeRenderedCode;
        currentCompilationNode = currentCompilationNode->nextNode();
    }
    mapping.insert("mainCodeList",mainCodeList);
    Grantlee::Context c(mapping);

    qDebug() <<"compilation : " << projectTemplate->render(&c);
}

QString BP_PythonManager::renderEventNode(BP_EventNode *node)
{
    return "#this is a event placeholder";
}

QString BP_PythonManager::renderFunctionNode(BP_FunctionNode *node)
{
    //return "this is a function placeholder";
    auto projectTemplate = grantleeEngine->loadByName("Python/templates/Function.j2");
    QVariantHash mapping ;
    mapping.insert("function",QVariant::fromValue(node->functionObject()));
    Grantlee::Context c(mapping);
    return projectTemplate->render(&c);
}

void BP_PythonManager::standardOutputReady()
{
    qDebug() << "Data Ready : " << m_managerProcess.readAllStandardOutput();
}

void BP_PythonManager::errorOutputReady()
{
    qDebug() << "Error Ready : " << m_managerProcess.readAllStandardError();
}
