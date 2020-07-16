/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020 by VisSim                                        *
 *                                                                         *
 *   Authors: Ibraheem Aldhamari, Yasser Grimes                            *
 *                                                                         *
 ***************************************************************************/
#ifndef IMPORTSMODEL_H
#define IMPORTSMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include <QTreeView>

#include <Modeling/Imports/bp_importsitem.h>

#include <Platform/bp_platformmanager.h>

#include <Core/bp_project.h>
class ImportsItemWidget;

class ImportsModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(BP_Project* connectedProject READ connectedProject WRITE setConnectedProject NOTIFY connectedProjectChanged)
public:
    ImportsModel();

    void importFromHieararchy(QStringList hierarchy);

    //Helper Functions
    QModelIndex indexForItem(BP_ImportsItem *importItem);
    BP_ImportsItem* itemForIndex(const QModelIndex &index) const;
    int rowForItem(BP_ImportsItem *item) const;
    void setupIndexesWidgets(BP_PlatformManager *platformManager);
    void setupItemWidget(BP_ImportsItem *item,BP_PlatformManager *platformManager);
    ImportsItemWidget* getWidgetForItem(BP_ImportsItem *item);

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    BP_ImportsItem *rootItem() const;
    void setRootItem(BP_ImportsItem *rootItem, ImportsModel *importModel);

    QTreeView *connectedView;

    BP_Project* connectedProject() const;

public slots:
    void setConnectedProject(BP_Project* connectedProject);

signals:
    void connectedProjectChanged(BP_Project* connectedProject);

private:
    BP_ImportsItem *m_rootItem;
    BP_Project* m_connectedProject;
};

#endif // IMPORTSMODEL_H
