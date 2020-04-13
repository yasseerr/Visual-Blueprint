/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_ONEVARIABLEMEMBERITEM_H
#define BP_ONEVARIABLEMEMBERITEM_H

#include "bp_memberitem.h"

#include <QWidget>

#include <Core/bp_variable.h>

class BP_OneVariableMemberItem : public BP_MemberItem
{
    Q_OBJECT
    Q_PROPERTY(BP_Variable* containedVariable READ containedVariable WRITE setContainedVariable NOTIFY containedVariableChanged)
    BP_Variable* m_containedVariable;

public:
    explicit BP_OneVariableMemberItem(BP_MemberItem *parentItem,QObject *parent = nullptr);

    BP_Variable* containedVariable() const;

public slots:
    void setContainedVariable(BP_Variable* containedVariable);
    void updateMemberName();

signals:
    void containedVariableChanged(BP_Variable* containedVariable);

    // BP_MemberItem interface
public:
    virtual QVariant getDesctiptionData(int role) override;
    virtual bool setDescriptionData(QVariant data, int role) override;
};

#endif // BP_ONEVARIABLEMEMBERITEM_H
