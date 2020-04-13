/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_MEMBERITEM_H
#define BP_MEMBERITEM_H

#include <QObject>
class BP_MemberModel;
class BP_MemberItem : public QObject
{
    Q_OBJECT
public:
    explicit BP_MemberItem(QObject *parent = nullptr);

    BP_MemberModel *m_model;
    BP_MemberItem *m_parentItem;
    QList<BP_MemberItem*> childItems;

signals:

};

#endif // BP_MEMBERITEM_H
