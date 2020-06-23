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

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <bp_utils.h>

#include <Core/bp_project.h>

#include <Graph/bp_graphview.h>
#include <Graph/bp_node.h>

#include <Graph/Nodes/bp_eventnode.h>
#include <Graph/Nodes/bp_floatnode.h>
#include <Graph/Nodes/bp_functionnode.h>
#include <Graph/Nodes/bp_intnode.h>
#include <Graph/Nodes/bp_stringnode.h>

#include <Graph/Links/bp_link.h>

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

void BP_PythonManager::loadBuiltins(BP_Project *project)
{
    QStringList returnList;

    m_managerProcess.setArguments(QStringList() << m_managerFile << "loadBuiltins");
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    QJsonArray listJson = QJsonDocument::fromJson(listRawData).array();
    auto builtinsList = listJson.toVariantList();
    foreach (auto builtinVariant, builtinsList ) {
        QVariantMap builinMap = builtinVariant.toMap();
        //TODO collapse to getCoreObjectFromVariant
        if(builinMap.value("type").toString() == "func"){
            BP_Function *builtinFunc = new BP_Function(&builinMap,project);
            project->addBuiltin(builtinFunc);
        }
        else if(builinMap.value("type").toString() == "var"){
            BP_Variable *builtinVar = new BP_Variable(&builinMap,project);
            project->addBuiltin(builtinVar);
        }
        else if(builinMap.value("type").toString() == "class"){
            BP_Class *builtinClass = new BP_Class(&builinMap,project);
            project->addBuiltin(builtinClass);
        }

    }
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
    qDebug() <<  listRawData;
    qDebug() << m_managerProcess.readAllStandardError();
    //QJsonParseError jsonError;
    QJsonObject jsonObject = QJsonDocument::fromJson(listRawData).object();
    //qDebug() << jsonError.errorString() << jsonError.offset;
    return jsonObject.toVariantMap();
}

QVariantMap BP_PythonManager::importFunction(QStringList moduleHiearchy)
{
    m_managerProcess.setArguments(QStringList() << m_managerFile << "importFunction" << moduleHiearchy);
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    qDebug() << listRawData.size();
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

    QString generatedCode = projectTemplate->render(&c);
    qDebug() << generatedCode.toUtf8();

    //saving to file
    QDir compilationDir = QApplication::applicationDirPath();
    if(!compilationDir.exists("Compilation")) compilationDir.mkdir("Compilation");
    compilationDir.cd("Compilation");

    QFile outputFile(compilationDir.path()+"/"+project->projectName()+".py");
    outputFile.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream ts(&outputFile);
    ts << generatedCode;
    outputFile.close();
}

void BP_PythonManager::runProject(BP_Project *project)
{
    compileProject(project);
    QString projectFilePath = "./Compilation/"+project->projectName()+".py";
    m_managerProcess.setArguments(QStringList() << projectFilePath);
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray executionOutput =  m_managerProcess.readAllStandardOutput();
    if(executionOutput.size()>0)BP_Utils::log(executionOutput,"PythonManager",BP_Utils::Info);
    QByteArray errorData  = m_managerProcess.readAllStandardError();
    if(errorData.size()>0)BP_Utils::log(errorData,"PythonManager",BP_Utils::Error);
}

QString BP_PythonManager::renderEventNode(BP_EventNode *node)
{
    return "#this is a event placeholder";
}

QString BP_PythonManager::renderFunctionNode(BP_FunctionNode *node)
{
    //return "this is a function placeholder";
    //rendering the variables nodes
    QStringList functionInputsDeclaration;
    foreach (auto inputSlot, node->inputParameters()) {
        if(inputSlot->connectedLinks().size()>0){
            functionInputsDeclaration << inputSlot->connectedLinks().first()->inSlot()->parentNode()->renderNode(this);
        }
    }

    auto projectTemplate = grantleeEngine->loadByName("Python/templates/Function.j2");
    QVariantHash mapping ;
    mapping.insert("function",QVariant::fromValue(node));
    mapping.insert("functionInputsDeclaration",functionInputsDeclaration);

    //temporary solution for parameter refrences
    QStringList parameterRefrences;
    foreach (auto paramSlot, node->inputParameters()) {
        //TODO support multipe links
        //TODO handle the different type of links
        if(paramSlot->connectedLinks().size()>0){
            parameterRefrences << paramSlot->connectedLinks().first()->inSlot()->reference();
        }
    }

    mapping.insert("parameterRefrences",parameterRefrences);

    Grantlee::Context c(mapping);
    return projectTemplate->render(&c);
}

QString BP_PythonManager::renderIntegerNode(BP_IntNode *node)
{
    return node->outputSlot()->reference()+" = "+QString::number(node->variableObject()->value().toInt());
}

QString BP_PythonManager::renderFloatNode(BP_FloatNode *node)
{
    return node->variableObject()->name()  + " = " + QString::number(node->variableObject()->value().toFloat());
}

QString BP_PythonManager::renderStringNode(BP_StringNode *node)
{
    return node->variableObject()->name()  + " = \"" + node->variableObject()->value().toString()+"\"";
}

void BP_PythonManager::standardOutputReady()
{
    qDebug() << "Data Ready : " << m_managerProcess.readAllStandardOutput();
}

void BP_PythonManager::errorOutputReady()
{
    qDebug() << "Error Ready : " << m_managerProcess.readAllStandardError();
}
