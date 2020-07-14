/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_CLASSINSTANCENODE_H
#define BP_CLASSINSTANCENODE_H

#include "bp_variablenode.h"

#include <QObject>

class BP_Class;
class BP_DataSlot;

//TODO create temporary instances
class BP_ClassInstanceNode : public BP_VariableNode
{
    Q_OBJECT
    Q_CLASSINFO("name","Instance")
    Q_PROPERTY(BP_Class* sourceClass READ sourceClass WRITE setSourceClass NOTIFY sourceClassChanged)
    Q_PROPERTY(int constructorId READ constructorId WRITE setConstructorId NOTIFY constructorIdChanged)
    Q_PROPERTY(QList<BP_DataSlot*> inputParameters READ inputParameters WRITE setInputParameters NOTIFY inputParametersChanged)
    BP_Class* m_sourceClass;

    int m_constructorId;

    QList<BP_DataSlot*> m_inputParameters;

public:
    Q_INVOKABLE BP_ClassInstanceNode();
    static int nodeTypeID ;

    QVariant toVariantBP() override;
    QString getNodeTypeString() override;

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void calculateBounds() override;

    // BP_Node interface
public:
    virtual QString renderNode(BP_PlatformManager *platform) override;

    BP_Class* sourceClass() const;
    int constructorId() const;

    QList<BP_DataSlot*> inputParameters() const;

public slots:
    void setSourceClass(BP_Class* sourceClass);
    void setConstructorId(int constructorId);

    void setInputParameters(QList<BP_DataSlot*> inputParameters);

signals:
    void sourceClassChanged(BP_Class* sourceClass);
    void constructorIdChanged(int constructorId);
    void inputParametersChanged(QList<BP_DataSlot*> inputParameters);
};

#endif // BP_CLASSINSTANCENODE_H
