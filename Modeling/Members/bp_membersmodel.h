/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_MEMBERSMODEL_H
#define BP_MEMBERSMODEL_H

#include "bp_memberitem.h"

#include <QAbstractItemModel>
#include <QObject>

class BP_MembersModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    BP_MembersModel();


    QModelIndex indexForItem(BP_MemberItem *importItem);
    BP_MemberItem* itemForIndex(const QModelIndex &index) const;
    int rowForItem(BP_MemberItem *item) const;

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
public:
    BP_MemberItem *m_rootItem;
};

#endif // BP_MEMBERSMODEL_H
