/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_membersmodel.h"

BP_MembersModel::BP_MembersModel(BP_Project *_project,QTreeView *connectedTreeView):
    m_connectedTreeView(connectedTreeView)
{
    m_rootItem = new BP_MemberItem(nullptr,this);
    m_rootItem->m_model = this;
    m_variablesItems = new BP_VariablesMemberItem(m_rootItem,m_rootItem);
    setConnectedProject(_project);
}

QModelIndex BP_MembersModel::indexForItem(BP_MemberItem *importItem)
{
    if(importItem == m_rootItem)
        return  QModelIndex();

    int rowNumber = rowForItem(importItem);
    int columnNumber = 0;
    return  createIndex(rowNumber,columnNumber,importItem);
}

QModelIndex BP_MembersModel::widgetIndexForItem(BP_MemberItem *importItem)
{
    if(importItem == m_rootItem)
        return  QModelIndex();

    int rowNumber = rowForItem(importItem);
    int columnNumber = 1;
    return  createIndex(rowNumber,columnNumber,importItem);
}

BP_MemberItem *BP_MembersModel::itemForIndex(const QModelIndex &index) const
{
    if(index.isValid())
        return  static_cast<BP_MemberItem*>(index.internalPointer());
    return  m_rootItem;
}

int BP_MembersModel::rowForItem(BP_MemberItem *item) const
{
    return  item->m_parentItem->childItems.indexOf(item);
}

QModelIndex BP_MembersModel::index(int row, int column, const QModelIndex &parent) const
{
    if(hasIndex(row,column,parent))
    {
        BP_MemberItem *parentItem = itemForIndex(parent);
        BP_MemberItem *childItem = parentItem->childItems.at(row);
        return  createIndex(row,column,childItem);
    }
    return  QModelIndex();
}

QModelIndex BP_MembersModel::parent(const QModelIndex &child) const
{
    BP_MemberItem *childItem = itemForIndex(child);
    BP_MemberItem *parentItem = childItem->m_parentItem;
    if(parentItem == m_rootItem)
        return  QModelIndex();
    int rowNumber = rowForItem(parentItem);
    int colNumber = 0;
    return  createIndex(rowNumber,colNumber,parentItem);
}

int BP_MembersModel::rowCount(const QModelIndex &parent) const
{
    BP_MemberItem *parentNode = itemForIndex(parent);
    return parentNode->childItems.size();
}

int BP_MembersModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant BP_MembersModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()){
        if(role == Qt::DisplayRole && index.column() == 0)
            return   itemForIndex(index)->memberName();
    }
    return QVariant();
}

Qt::ItemFlags BP_MembersModel::flags(const QModelIndex &index) const
{
    return  QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

BP_Project *BP_MembersModel::connectedProject() const
{
    return m_connectedProject;
}

void BP_MembersModel::updateModel()
{
    if(m_connectedProject == nullptr) return;
    //loading variables


}

void BP_MembersModel::setConnectedProject(BP_Project *connectedProject)
{
    if (m_connectedProject == connectedProject)
        return;
    m_connectedProject = connectedProject;



    emit connectedProjectChanged(m_connectedProject);
}
