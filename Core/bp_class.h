/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_CLASS_H
#define BP_CLASS_H

#include <QObject>

class BP_Function;
class BP_Variable;
class BP_Module;

class BP_Class : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString className READ className WRITE setClassName NOTIFY classNameChanged)
    Q_PROPERTY(QList<BP_Variable*> memberVariables READ memberVariables WRITE setMemberVariables NOTIFY memberVariablesChanged)
    Q_PROPERTY(QList<BP_Function*> memberFunctions READ memberFunctions WRITE setMemberFunctions NOTIFY memberFunctionsChanged)
    Q_PROPERTY(BP_Module* owningModule READ owningModule WRITE setOwningModule NOTIFY owningModuleChanged)
    Q_PROPERTY(QStringList moduleHierarchy READ moduleHierarchy WRITE setModuleHierarchy NOTIFY moduleHierarchyChanged)
    QString m_className;

    QList<BP_Variable*> m_memberVariables;

    QList<BP_Function*> m_memberFunctions;

    BP_Module* m_owningModule;

    QStringList m_moduleHierarchy;

public:
    explicit BP_Class(QObject *parent = nullptr);

    QString className() const;

    QList<BP_Variable*> memberVariables() const
    {
        return m_memberVariables;
    }

    QList<BP_Function*> memberFunctions() const
    {
        return m_memberFunctions;
    }

    BP_Module* owningModule() const
    {
        return m_owningModule;
    }

    QStringList moduleHierarchy() const
    {
        return m_moduleHierarchy;
    }

public slots:
    void setClassName(QString className);

    void setMemberVariables(QList<BP_Variable*> memberVariables)
    {
        if (m_memberVariables == memberVariables)
            return;

        m_memberVariables = memberVariables;
        emit memberVariablesChanged(m_memberVariables);
    }

    void setMemberFunctions(QList<BP_Function*> memberFunctions)
    {
        if (m_memberFunctions == memberFunctions)
            return;

        m_memberFunctions = memberFunctions;
        emit memberFunctionsChanged(m_memberFunctions);
    }

    void setOwningModule(BP_Module* owningModule)
    {
        if (m_owningModule == owningModule)
            return;

        m_owningModule = owningModule;
        emit owningModuleChanged(m_owningModule);
    }

    void setModuleHierarchy(QStringList moduleHierarchy)
    {
        if (m_moduleHierarchy == moduleHierarchy)
            return;

        m_moduleHierarchy = moduleHierarchy;
        emit moduleHierarchyChanged(m_moduleHierarchy);
    }

signals:

    void classNameChanged(QString className);
    void memberVariablesChanged(QList<BP_Variable*> memberVariables);
    void memberFunctionsChanged(QList<BP_Function*> memberFunctions);
    void owningModuleChanged(BP_Module* owningModule);
    void moduleHierarchyChanged(QStringList moduleHierarchy);
};

#endif // BP_CLASS_H
