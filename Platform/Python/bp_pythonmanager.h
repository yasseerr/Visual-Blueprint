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
    virtual void runProject(BP_Project *project) override;

    QString renderEventNode(BP_EventNode *node) override;
    QString renderFunctionNode(BP_FunctionNode *node) override;
    QString renderIntegerNode(BP_IntNode *node) override;
    QString renderStringNode(BP_StringNode *node) override;

public slots:
    virtual void standardOutputReady() override;
    virtual void errorOutputReady() override;

};

#endif // BP_PYTHONMANAGER_H
