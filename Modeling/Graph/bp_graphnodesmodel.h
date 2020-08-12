/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_GRAPHNODESMODEL_H
#define BP_GRAPHNODESMODEL_H

#include "bp_graphnodeitem.h"

#include <QAbstractItemModel>
#include <QObject>

#include <Core/bp_project.h>

class BP_GraphNodesModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(BP_GraphNodeItem* rootItem READ rootItem WRITE setRootItem NOTIFY rootItemChanged)
    Q_PROPERTY(BP_Project* connectedProject READ connectedProject WRITE setConnectedProject NOTIFY connectedProjectChanged)
    BP_GraphNodeItem* m_rootItem;

    BP_Project* m_connectedProject;

public:
    BP_GraphNodesModel(BP_Project *connectedProject = nullptr);

    //Helper Functions
    QModelIndex indexForItem(BP_GraphNodeItem *importItem);
    BP_GraphNodeItem* itemForIndex(const QModelIndex &index) const;
    int rowForItem(BP_GraphNodeItem *item) const;
    BP_GraphNodeItem* getCoreObjectNode(BP_CoreObject *obj);

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    BP_GraphNodeItem* rootItem() const;
    BP_Project* connectedProject() const;

public slots:
    void updateModule();

    void setRootItem(BP_GraphNodeItem* rootItem);
    void setConnectedProject(BP_Project* connectedProject);

signals:
    void rootItemChanged(BP_GraphNodeItem* rootItem);
    void connectedProjectChanged(BP_Project* connectedProject);

    //notify the proxy models
    void contentChanged();
};

#endif // BP_GRAPHNODESMODEL_H
