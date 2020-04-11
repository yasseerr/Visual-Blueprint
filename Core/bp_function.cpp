/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_function.h"
#include "bp_parameter.h"

#include <QVariantMap>

BP_Function::BP_Function(QVariantMap *functionMap,QObject *parent) : QObject(parent),
    m_functionName(""),
    m_returnArg(nullptr),
    m_owningClass(nullptr),
    m_owningModule(nullptr),
    m_isMember(false),
    m_hasKeyWords(false),
    m_hasPositional(false),
    m_isFullyImported(false)
{
    if(functionMap != nullptr){

        m_functionName = functionMap->value("name").toString();
        m_hasPositional = functionMap->value("hasPositional").toBool();
        m_hasKeyWords = functionMap->value("hasPositional").toBool();

        foreach (auto paramVariant, functionMap->value("inputs").toList()) {
            QVariantMap paramMap = paramVariant.toMap();
            BP_Parameter *newParmeter = new BP_Parameter(this,&paramMap);
            m_inputArgs << newParmeter;
        }
    }

}

QString BP_Function::functionName() const
{
    return m_functionName;
}

QList<BP_Parameter *> BP_Function::inputArgs() const
{
    return m_inputArgs;
}

BP_Parameter *BP_Function::returnArg() const
{
    return m_returnArg;
}

BP_Class *BP_Function::owningClass() const
{
    return m_owningClass;
}

BP_Module *BP_Function::owningModule() const
{
    return m_owningModule;
}

bool BP_Function::isMember() const
{
    return m_isMember;
}

bool BP_Function::hasKeyWords() const
{
    return m_hasKeyWords;
}

bool BP_Function::hasPositional() const
{
    return m_hasPositional;
}

bool BP_Function::isFullyImported() const
{
    return m_isFullyImported;
}

void BP_Function::setFunctionName(QString functionName)
{
    if (m_functionName == functionName)
        return;

    m_functionName = functionName;
    emit functionNameChanged(m_functionName);
}

void BP_Function::setInputArgs(QList<BP_Parameter *> inputArgs)
{
    if (m_inputArgs == inputArgs)
        return;

    m_inputArgs = inputArgs;
    emit inputArgsChanged(m_inputArgs);
}

void BP_Function::setReturnArg(BP_Parameter *returnArg)
{
    if (m_returnArg == returnArg)
        return;

    m_returnArg = returnArg;
    emit returnArgChanged(m_returnArg);
}

void BP_Function::setOwningClass(BP_Class *owningClass)
{
    if (m_owningClass == owningClass)
        return;

    m_owningClass = owningClass;
    emit owningClassChanged(m_owningClass);
}

void BP_Function::setOwningModule(BP_Module *owningModule)
{
    if (m_owningModule == owningModule)
        return;

    m_owningModule = owningModule;
    emit owningModuleChanged(m_owningModule);
}

void BP_Function::setIsMember(bool isMember)
{
    if (m_isMember == isMember)
        return;

    m_isMember = isMember;
    emit isMemberChanged(m_isMember);
}

void BP_Function::setHasKeyWords(bool hasKeyWords)
{
    if (m_hasKeyWords == hasKeyWords)
        return;

    m_hasKeyWords = hasKeyWords;
    emit hasKeyWordsChanged(m_hasKeyWords);
}

void BP_Function::setHasPositional(bool hasPositional)
{
    if (m_hasPositional == hasPositional)
        return;

    m_hasPositional = hasPositional;
    emit hasPositionalChanged(m_hasPositional);
}

void BP_Function::setIsFullyImported(bool isFullyImported)
{
    if (m_isFullyImported == isFullyImported)
        return;

    m_isFullyImported = isFullyImported;
    emit isFullyImportedChanged(m_isFullyImported);
}
