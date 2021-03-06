/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_PYTHONMANAGER_H
#define BP_PYTHONMANAGER_H

#include <QObject>

#include <Platform/bp_platformmanager.h>

class BP_PythonManager : public BP_PlatformManager
{
    Q_OBJECT
public:
    BP_PythonManager(QObject *parent =  nullptr);

    QMap<QString,QString> defaultOperationSymbols;
    QMap<QString,QString> memberFunctionsMap;


    // BP_PlatformManager interface
public:
    virtual QStringList listGlobalModules() override;
    void loadBuiltins(BP_Project *project) override;
    virtual QList<QPair<QString, QString> > inspectModuleByName(QStringList moduleHierchy) override;
    virtual QVariantMap importModule(QStringList moduleHiearchy) override;
    virtual QVariantMap importFunction(QStringList moduleHiearchy) override;
    virtual QVariantMap importVariable(QStringList moduleHiearchy) override;
    virtual QVariantMap importClass(QStringList moduleHiearchy) override;
    virtual void compileProject(BP_Project *project) override;
    QStringList compileBlock(BP_Node *startNode, BP_Node *endNode) override;
    QString appendMemberFunction(BP_Node *startNode, QString functionName,QStringList args,
                                 BP_Node *endNode = nullptr,bool isAsync = false) override;
    virtual void runProject(BP_Project *project) override;
    void clearCompilationVariables(BP_Project *project) override;

    QString renderEventNode(BP_EventNode *node) override;
    QString renderFunctionNode(BP_FunctionNode *node) override;
    QString renderIntegerNode(BP_IntNode *node) override;
    QString renderFloatNode(BP_FloatNode *node) override;
    QString renderStringNode(BP_StringNode *node) override;
    QString renderBoolNode(BP_BoolNode *node) override;
    QString renderClassInstanceNode(BP_ClassInstanceNode *node) override;
    QString renderIFStatement(BP_IFNode *node) override;
    QString renderLoopStatement(BP_LoopNode *node) override;

    //threads
    QString renderCreateThreadsNode(BP_CreateThreadsNode *node) override;
    QString renderRunAsyncNode(BP_RunAsyncNode *node) override;

    //Operaions Tools
    //helper function
    QString renderDefaultOperationTool(BP_OperationToolNode *node, QString operationName) override;
    //QString renderAdditionNode(BP_AddNode *node) override;
    QString renderScopeNodes(BP_Node *node) override;
    void insertBasicNodeValues(BP_Node *node,QVariantHash &hash);

    //doc
    QString getDocForCoreObject(BP_CoreObject *obj) override;

    BP_Class * getBasicTypeClass(QString typeName) override;

public slots:
    virtual void standardOutputReady() override;
    virtual void errorOutputReady() override;

};

#endif // BP_PYTHONMANAGER_H
