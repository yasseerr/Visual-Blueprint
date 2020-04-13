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

class BP_OneVariableMemberItem : public BP_MemberItem
{
    Q_OBJECT
public:
    explicit BP_OneVariableMemberItem(BP_MemberItem *parentItem,QObject *parent = nullptr);

signals:

};

#endif // BP_ONEVARIABLEMEMBERITEM_H
