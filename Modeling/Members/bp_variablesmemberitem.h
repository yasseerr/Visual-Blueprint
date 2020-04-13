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

class BP_VariablesMemberItem : public BP_MemberItem
{
    Q_OBJECT
public:
    explicit BP_VariablesMemberItem(QObject *parent = nullptr);

signals:

};

#endif // BP_VARIABLESMEMBERITEM_H
