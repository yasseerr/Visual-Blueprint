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

#include "bp_coreobject.h"

#include <QObject>
#include <QVariantMap>


class BP_Function;
class BP_Variable;
class BP_Module;
class BP_Constructor;

class BP_Class : public BP_CoreObject
{
    Q_OBJECT
    Q_PROPERTY(QList<BP_Variable*> memberVariables READ memberVariables WRITE setMemberVariables NOTIFY memberVariablesChanged)
    Q_PROPERTY(QList<BP_Function*> memberFunctions READ memberFunctions WRITE setMemberFunctions NOTIFY memberFunctionsChanged)
    Q_PROPERTY(BP_Module* owningModule READ owningModule WRITE setOwningModule NOTIFY owningModuleChanged)
    Q_PROPERTY(QList<BP_Constructor*> constructors READ constructors WRITE setConstructors NOTIFY constructorsChanged)


    QList<BP_Variable*> m_memberVariables;

    QList<BP_Function*> m_memberFunctions;

    BP_Module* m_owningModule;

    QStringList m_moduleHierarchy;

    QList<BP_Constructor*> m_constructors;

public:
    explicit BP_Class(QVariantMap *variableMap = nullptr,QObject *parent = nullptr);

    //QVariant toVariantBP() override;

    QList<BP_Variable*> memberVariables() const;

    QList<BP_Function*> memberFunctions() const;

    BP_Module* owningModule() const;

    QList<BP_Constructor*> constructors() const;

    BP_Node * createNodeForObject(QObject *parent = nullptr) override;

public slots:


    void setMemberVariables(QList<BP_Variable*> memberVariables);

    void setMemberFunctions(QList<BP_Function*> memberFunctions);

    void setOwningModule(BP_Module* owningModule);

    void setConstructors(QList<BP_Constructor*> constructors);

signals:

    void memberVariablesChanged(QList<BP_Variable*> memberVariables);
    void memberFunctionsChanged(QList<BP_Function*> memberFunctions);
    void owningModuleChanged(BP_Module* owningModule);
    void constructorsChanged(QList<BP_Constructor*> constructors);
};

#endif // BP_CLASS_H
