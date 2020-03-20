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

#include <Modeling/Imports/bp_importsitem.h>

class ImportsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ImportsModel();

    //Helper Functions
    QModelIndex indexForItem(BP_ImportsItem *importItem);
    BP_ImportsItem* itemForIndex(const QModelIndex &index) const;
    int rowForItem(BP_ImportsItem *item) const;

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    BP_ImportsItem *rootItem() const;
    void setRootItem(BP_ImportsItem *rootItem);

private:
    BP_ImportsItem *m_rootItem;
};

#endif // IMPORTSMODEL_H
