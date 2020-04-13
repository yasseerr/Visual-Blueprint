/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_VARIABLESMEMBERITEM_H
#define BP_VARIABLESMEMBERITEM_H

#include "bp_memberitem.h"

#include <QObject>
#include <QToolBar>

class BP_VariablesMemberItem : public BP_MemberItem
{
    Q_OBJECT

    QToolBar *variablesToolBar;

public:
    explicit BP_VariablesMemberItem(BP_MemberItem *parentItem,QObject *parent = nullptr);
    void createVariablesMenu(const QList<QAction*> mainWindowAction);


signals:

};

#endif // BP_VARIABLESMEMBERITEM_H
