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
#include <QVariantMap>

class BP_Function;
class BP_Variable;
class BP_Module;
class BP_Constructor;

class BP_Class : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString className READ className WRITE setClassName NOTIFY classNameChanged)
    Q_PROPERTY(QList<BP_Variable*> memberVariables READ memberVariables WRITE setMemberVariables NOTIFY memberVariablesChanged)
    Q_PROPERTY(QList<BP_Function*> memberFunctions READ memberFunctions WRITE setMemberFunctions NOTIFY memberFunctionsChanged)
    Q_PROPERTY(BP_Module* owningModule READ owningModule WRITE setOwningModule NOTIFY owningModuleChanged)
    Q_PROPERTY(QStringList moduleHierarchy READ moduleHierarchy WRITE setModuleHierarchy NOTIFY moduleHierarchyChanged)
    Q_PROPERTY(QList<BP_Constructor*> constructors READ constructors WRITE setConstructors NOTIFY constructorsChanged)

    QString m_className;

    QList<BP_Variable*> m_memberVariables;

    QList<BP_Function*> m_memberFunctions;

    BP_Module* m_owningModule;

    QStringList m_moduleHierarchy;

    QList<BP_Constructor*> m_constructors;

public:
    explicit BP_Class(QVariantMap *variableMap = nullptr,QObject *parent = nullptr);

    QString className() const;

    QList<BP_Variable*> memberVariables() const;

    QList<BP_Function*> memberFunctions() const;

    BP_Module* owningModule() const;

    QStringList moduleHierarchy() const;

    QList<BP_Constructor*> constructors() const;

public slots:
    void setClassName(QString className);

    void setMemberVariables(QList<BP_Variable*> memberVariables);

    void setMemberFunctions(QList<BP_Function*> memberFunctions);

    void setOwningModule(BP_Module* owningModule);

    void setModuleHierarchy(QStringList moduleHierarchy);

    void setConstructors(QList<BP_Constructor*> constructors);

signals:

    void classNameChanged(QString className);
    void memberVariablesChanged(QList<BP_Variable*> memberVariables);
    void memberFunctionsChanged(QList<BP_Function*> memberFunctions);
    void owningModuleChanged(BP_Module* owningModule);
    void moduleHierarchyChanged(QStringList moduleHierarchy);
    void constructorsChanged(QList<BP_Constructor*> constructors);
};

#endif // BP_CLASS_H
