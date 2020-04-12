/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_FUNCTION_H
#define BP_FUNCTION_H

#include "bp_coreobject.h"

#include <QObject>

class BP_Parameter;
class BP_Module;
class BP_Class;

class BP_Function : public BP_CoreObject
{
    Q_OBJECT
    Q_PROPERTY(QList<BP_Parameter*> inputArgs READ inputArgs WRITE setInputArgs NOTIFY inputArgsChanged)
    Q_PROPERTY(BP_Parameter* returnArg READ returnArg WRITE setReturnArg NOTIFY returnArgChanged)
    Q_PROPERTY(BP_Module* owningModule READ owningModule WRITE setOwningModule NOTIFY owningModuleChanged)
    Q_PROPERTY(BP_Class* owningClass READ owningClass WRITE setOwningClass NOTIFY owningClassChanged)
    Q_PROPERTY(bool isMember READ isMember WRITE setIsMember NOTIFY isMemberChanged)
    Q_PROPERTY(bool hasKeyWords READ hasKeyWords WRITE setHasKeyWords NOTIFY hasKeyWordsChanged)
    Q_PROPERTY(bool hasPositional READ hasPositional WRITE setHasPositional NOTIFY hasPositionalChanged)
    Q_PROPERTY(bool isFullyImported READ isFullyImported WRITE setIsFullyImported NOTIFY isFullyImportedChanged)

    //members
    QString m_functionName;
    QList<BP_Parameter*> m_inputArgs;
    BP_Parameter* m_returnArg;
    BP_Class* m_owningClass;
    BP_Module* m_owningModule;
    bool m_isMember;
    bool m_hasKeyWords;
    bool m_hasPositional;
    bool m_isFullyImported;

public:
    explicit BP_Function(QVariantMap *functionMap,QObject *parent = nullptr);

    QList<BP_Parameter*> inputArgs() const;

    BP_Parameter* returnArg() const;

    BP_Class* owningClass() const;

    BP_Module* owningModule() const;

    bool isMember() const;

    bool hasKeyWords() const;

    bool hasPositional() const;

    bool isFullyImported() const;

public slots:

    void setInputArgs(QList<BP_Parameter*> inputArgs);


    void setReturnArg(BP_Parameter* returnArg);

    void setOwningClass(BP_Class* owningClass);

    void setOwningModule(BP_Module* owningModule);

    void setIsMember(bool isMember);

    void setHasKeyWords(bool hasKeyWords);

    void setHasPositional(bool hasPositional);

    void setIsFullyImported(bool isFullyImported);

signals:

    void inputArgsChanged(QList<BP_Parameter*> inputArgs);
    void returnArgChanged(BP_Parameter* returnArg);
    void owningClassChanged(BP_Class* owningClass);
    void owningModuleChanged(BP_Module* owningModule);
    void isMemberChanged(bool isMember);
    void hasKeyWordsChanged(bool hasKeyWords);
    void hasPositionalChanged(bool hasPositional);
    void isFullyImportedChanged(bool isFullyImported);
};

#endif // BP_FUNCTION_H
