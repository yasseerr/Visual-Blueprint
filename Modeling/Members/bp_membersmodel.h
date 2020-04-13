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
#include "bp_variablesmemberitem.h"

#include <QAbstractItemModel>
#include <QObject>
#include <QTreeView>

class BP_Project;
class BP_VariablesMemberItem;

class BP_MembersModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(BP_Project* connectedProject READ connectedProject WRITE setConnectedProject NOTIFY connectedProjectChanged)
    BP_Project* m_connectedProject;

public:
    BP_MembersModel(BP_Project *_project,QTreeView *connectedTreeView =nullptr);


    QModelIndex indexForItem(BP_MemberItem *importItem);
    QModelIndex widgetIndexForItem(BP_MemberItem *importItem);
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
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    BP_Project* connectedProject() const;

public:
    BP_MemberItem *m_rootItem;
    BP_VariablesMemberItem *m_variablesItems;
    QTreeView *m_connectedTreeView;

public slots:

    void updateModel();
    void addMemberVariable();

    void setConnectedProject(BP_Project *connectedProject);
signals:
    void connectedProjectChanged(BP_Project* connectedProject);
};

#endif // BP_MEMBERSMODEL_H
