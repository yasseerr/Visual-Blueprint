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
class BP_MembersModel;
class BP_MemberItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString memberName READ memberName WRITE setMemberName NOTIFY memberNameChanged)

    QString m_memberName;

public:
    explicit BP_MemberItem(BP_MemberItem *parentItem,QObject *parent = nullptr);

    BP_MembersModel *m_model;
    BP_MemberItem *m_parentItem;
    QList<BP_MemberItem*> childItems;

    QString memberName() const;

public slots:
    void setMemberName(QString memberName);

signals:

    void memberNameChanged(QString memberName);
};

#endif // BP_MEMBERITEM_H
