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
#include "bp_onevariablememberitem.h"

#include <Core/bp_project.h>

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
        if(index.column() == 1){
            return  itemForIndex(index)->getDesctiptionData(role);
        }
    }
    return QVariant();
}

Qt::ItemFlags BP_MembersModel::flags(const QModelIndex &index) const
{
    if(itemForIndex(index)->m_parentItem == m_rootItem ) return QAbstractItemModel::flags(index);
    return  QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled ;
}

bool BP_MembersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) return false;
    BP_MemberItem *selectedMemberItem = itemForIndex(index);
    if(index.column() == 0){
        //TODO add check for the variable name
        selectedMemberItem->setMemberName(value.toString());
        emit dataChanged(index,index,QVector<int>()<<Qt::DisplayRole);
    }else if (index.column() == 1) {
        selectedMemberItem->setDescriptionData(value,role);
        emit dataChanged(index,index,QVector<int>()<<Qt::DisplayRole <<Qt::DecorationRole);
    }
    return  false;
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

void BP_MembersModel::addMemberVariable()
{
    BP_OneVariableMemberItem *variableMemberItem = new BP_OneVariableMemberItem(m_variablesItems,m_variablesItems);
    QVariantMap newVariableMap = BP_Variable::getDefaultVariantMap();
    BP_Variable *newVariable = new BP_Variable(&newVariableMap,m_connectedProject);
    newVariable->setIsImported(false);
    newVariable->setIsProjectMember(true);
    variableMemberItem->setContainedVariable(newVariable);
    m_connectedProject->addMemberVariable(newVariable);
    emit layoutChanged();
    m_connectedTreeView->edit(indexForItem(variableMemberItem));

}

void BP_MembersModel::addMemberVariableFromVariant(QVariantMap memberVariant)
{
    //create the variable
    //add it to the members treeview
    BP_OneVariableMemberItem *variableMemberItem = new BP_OneVariableMemberItem(m_variablesItems,m_variablesItems);
    BP_Variable *newVariable = new BP_Variable(&memberVariant,m_connectedProject);
    newVariable->setIsImported(false);
    newVariable->setIsProjectMember(true);
    variableMemberItem->setContainedVariable(newVariable);
    m_connectedProject->addMemberVariable(newVariable);
    emit layoutChanged();
    //link the nodes to it using getMemberVariableByName
}

void BP_MembersModel::setConnectedProject(BP_Project *connectedProject)
{
    if (m_connectedProject == connectedProject)
        return;
    m_connectedProject = connectedProject;



    emit connectedProjectChanged(m_connectedProject);
}
