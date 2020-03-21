/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020 by AFKAAR                                          *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *                                                                         *
 ***************************************************************************/
#include "importsmodel.h"

#include <QLabel>
#include <QPushButton>
#include <QTextEdit>

#include <Widgets/importsitemwidget.h>

ImportsModel::ImportsModel()
{

}

QModelIndex ImportsModel::indexForItem(BP_ImportsItem *importItem)
{
    if(importItem == m_rootItem)
        return  QModelIndex();

    int rowNumber = rowForItem(importItem);
    int columnNumber = 0;
    return  createIndex(rowNumber,columnNumber,importItem);
}

BP_ImportsItem *ImportsModel::itemForIndex(const QModelIndex &index) const
{
    if(index.isValid())
        return  static_cast<BP_ImportsItem*>(index.internalPointer());
    return  m_rootItem;
}

int ImportsModel::rowForItem(BP_ImportsItem *item) const
{
    return  item->m_parentItem->childItems.indexOf(item);
}

void ImportsModel::setupIndexesWidgets()
{
    foreach (auto childItem, m_rootItem->childItems) {
        int childRow = rowForItem(childItem);
        connectedView->setIndexWidget(createIndex(childRow,1,childItem),
                                      new ImportsItemWidget(childItem,createIndex(childRow,1,childItem)));
    }
}



QModelIndex ImportsModel::index(int row, int column, const QModelIndex &parent) const
{
    if(hasIndex(row,column,parent))
    {
        BP_ImportsItem *parentItem = itemForIndex(parent);
        BP_ImportsItem *childItem = parentItem->childItems.at(row);
        return  createIndex(row,column,childItem);
    }
    return  QModelIndex();
}

QModelIndex ImportsModel::parent(const QModelIndex &child) const
{
    BP_ImportsItem *childItem = itemForIndex(child);
    BP_ImportsItem *parentItem = childItem->m_parentItem;
    if(parentItem == m_rootItem)
        return  QModelIndex();
    int rowNumber = rowForItem(parentItem);
    int colNumber = 0;
    return  createIndex(rowNumber,colNumber,parentItem);
}

int ImportsModel::rowCount(const QModelIndex &parent) const
{
    BP_ImportsItem *parentNode = itemForIndex(parent);
    return parentNode->childItems.size();
}

int ImportsModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ImportsModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role==Qt::DisplayRole)
    {
        if(index.column() == 0){
            BP_ImportsItem *importItem = itemForIndex(index);
            return  importItem->m_name;
        }
        else if (index.column() == 1) {
            //connectedView->setIndexWidget(index,new QLabel("import"));
            return "";
        }
    }
//    if (index.isValid() && role==Qt::DecorationRole) {
//        vsNavigatorNode *nNode = nodeForIndex(index);
//        return QVariant::fromValue(QPixmap(nNode->iconPath));
//    }
    return QVariant();
}

BP_ImportsItem *ImportsModel::rootItem() const
{
    return m_rootItem;
}

void ImportsModel::setRootItem(BP_ImportsItem *rootItem)
{
    m_rootItem = rootItem;
}
