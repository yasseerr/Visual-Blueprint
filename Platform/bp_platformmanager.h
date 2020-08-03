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

#include <grantlee/engine.h>
#include <grantlee_templates.h>
#include <grantlee_textdocument.h>

class BP_Project;
class BP_EventNode;
class BP_FunctionNode;
class BP_VariableNode;
class BP_IntNode;
class BP_StringNode;
class BP_FloatNode;
class BP_ClassInstanceNode;
class BP_Node;
class BP_IFNode;
class BP_LoopNode;
class BP_BoolNode;

class BP_AddNode;
class BP_OperationToolNode;

class BP_CreateThreadsNode;

class BP_PlatformManager : public QObject
{
    Q_OBJECT
public:
    explicit BP_PlatformManager(QObject *parent = nullptr);

    //classes to implement according to Framwork/languages
    virtual QStringList listGlobalModules() = 0;
    virtual void loadBuiltins(BP_Project *project) = 0;
    virtual QList<QPair<QString,QString>> inspectModuleByName(QStringList moduleHierarchy) = 0;
    virtual QVariantMap importModule(QStringList moduleHiearchy) = 0;
    virtual QVariantMap importFunction(QStringList moduleHiearchy) = 0;
    virtual QVariantMap importVariable(QStringList moduleHiearchy) = 0;
    virtual QVariantMap importClass(QStringList moduleHiearchy) = 0;

    virtual void compileProject(BP_Project *project) = 0;
    virtual QStringList compileBlock(BP_Node *startNode,BP_Node *endNode) = 0;
    virtual QString appendMemberFunction(BP_Node* startNode,QString functionName) = 0;
    virtual void runProject(BP_Project *project) = 0;
    virtual void clearCompilationVariables(BP_Project *project) = 0;


    virtual QString renderEventNode(BP_EventNode *node) = 0;
    virtual QString renderFunctionNode(BP_FunctionNode *node) = 0;
    virtual QString renderIntegerNode(BP_IntNode *node) = 0;
    virtual QString renderFloatNode(BP_FloatNode *node) = 0;
    virtual QString renderStringNode(BP_StringNode *node) = 0;
    virtual QString renderBoolNode(BP_BoolNode *node) = 0;
    virtual QString renderClassInstanceNode(BP_ClassInstanceNode *node) = 0;
    virtual QString renderIFStatement(BP_IFNode *node) = 0;
    virtual QString renderLoopStatement(BP_LoopNode *node) = 0;

    //threads
    virtual QString renderCreateThreadsNode(BP_CreateThreadsNode *node) = 0;


    //OperationTools Nodes
    //Note the implemetation of this funciton should be accompagnied with a map for operations
    virtual QString renderDefaultOperationTool(BP_OperationToolNode *node,QString operationName) = 0;
    //virtual QString renderAdditionNode(BP_AddNode *node) = 0;
    virtual QString renderScopeNodes(BP_Node *node) = 0;


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
    QProcess m_runningProcess;
    Grantlee::Engine *grantleeEngine;




};

#endif // BP_PLATFORMMANAGER_H
