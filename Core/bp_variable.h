/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_VARIABLE_H
#define BP_VARIABLE_H

#include "bp_coreobject.h"

#include <QObject>
#include <QVariant>

class BP_Class;
class BP_Module;
class BP_Parameter;

class BP_Variable : public BP_CoreObject
{
    Q_OBJECT
    Q_PROPERTY(QString className READ className WRITE setClassName NOTIFY classNameChanged)
    Q_PROPERTY(QStringList classModuleHiearchy READ classModuleHiearchy WRITE setClassModuleHiearchy NOTIFY classModuleHiearchyChanged)
    Q_PROPERTY(bool isPrimitive READ isPrimitive WRITE setIsPrimitive NOTIFY isPrimitiveChanged)
    Q_PROPERTY(bool isArray READ isArray WRITE setIsArray NOTIFY isArrayChanged)
    Q_PROPERTY(bool isMember READ isMember WRITE setIsMember NOTIFY isMemberChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(BP_Class* sourceClass READ sourceClass WRITE setSourceClass NOTIFY sourceClassChanged)
    Q_PROPERTY(BP_Class* owningClass READ owningClass WRITE setOwningClass NOTIFY owningClassChanged)
    Q_PROPERTY(BP_Module* owningModule READ owningModule WRITE setOwningModule NOTIFY owningModuleChanged)


    bool m_isPrimitive;

    bool m_isArray;

    bool m_isMember;

    QVariant m_value;

    BP_Class* m_owningClass;

    BP_Module* m_owningModule;

    QString m_className;

    QStringList m_classModuleHiearchy;

    BP_Class* m_sourceClass;


public:
    explicit BP_Variable(QVariantMap *variableMap = nullptr,QObject *parent = nullptr,QStringList *moduleHiearchy = nullptr);

    static QVariantMap getDefaultVariantMap();

    virtual void getAsParameter(BP_Parameter* param);
    QVariantMap getVariableAsVariant();

    bool isPrimitive() const;

    bool isArray() const;

    bool isMember() const;

    QVariant value() const;

    BP_Class* owningClass() const;

    BP_Module* owningModule() const;

    QString className() const;

    QStringList classModuleHiearchy() const;

public slots:

    void setIsPrimitive(bool isPrimitive);

    void setIsArray(bool isArray);

    void setIsMember(bool isMember);

    void setValue(QVariant value);

    void setOwningClass(BP_Class* owningClass);

    void setOwningModule(BP_Module* owningModule);

    void setClassName(QString className);

    void setClassModuleHiearchy(QStringList classModuleHiearchy);

    void setSourceClass(BP_Class* sourceClass);


signals:
    void isPrimitiveChanged(bool isPrimitive);
    void isArrayChanged(bool isArray);
    void isMemberChanged(bool isMember);
    void valueChanged(QVariant value);
    void owningClassChanged(BP_Class* owningClass);
    void owningModuleChanged(BP_Module* owningModule);
    void classNameChanged(QString className);
    void classModuleHiearchyChanged(QStringList classModuleHiearchy);

    // BP_CoreObject interface
    void sourceClassChanged(BP_Class* sourceClass);


public:
virtual BP_Node *createNodeForObject(BP_Slot *selfSlot,QObject *parent) override;
BP_Class* sourceClass() const;

};

#endif // BP_VARIABLE_H
