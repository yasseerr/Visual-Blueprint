/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_graphnodesmodel.h"

#include <Core/bp_class.h>
#include <Core/bp_function.h>
#include <Core/bp_module.h>
#include <Core/bp_variable.h>

BP_GraphNodesModel::BP_GraphNodesModel(BP_Project *connectedProject):QAbstractItemModel()
{
    m_rootItem = new BP_GraphNodeItem();
    if(connectedProject != nullptr)setConnectedProject(connectedProject);
}

QModelIndex BP_GraphNodesModel::indexForItem(BP_GraphNodeItem *importItem)
{
    if(importItem == m_rootItem)
        return  QModelIndex();

    int rowNumber = rowForItem(importItem);
    int columnNumber = 0;
    return  createIndex(rowNumber,columnNumber,importItem);
}

BP_GraphNodeItem *BP_GraphNodesModel::itemForIndex(const QModelIndex &index) const
{
    if(index.isValid())
        return  static_cast<BP_GraphNodeItem*>(index.internalPointer());
    return  m_rootItem;
}

int BP_GraphNodesModel::rowForItem(BP_GraphNodeItem *item) const
{
    return  item->m_parentItem->childItems.indexOf(item);
}

QModelIndex BP_GraphNodesModel::index(int row, int column, const QModelIndex &parent) const
{
    if(hasIndex(row,column,parent))
    {
        BP_GraphNodeItem *parentItem = itemForIndex(parent);
        BP_GraphNodeItem *childItem = parentItem->childItems.at(row);
        return  createIndex(row,column,childItem);
    }
    return  QModelIndex();
}

QModelIndex BP_GraphNodesModel::parent(const QModelIndex &child) const
{
    BP_GraphNodeItem *childItem = itemForIndex(child);
    BP_GraphNodeItem *parentItem = childItem->m_parentItem;
    if(parentItem == m_rootItem)
        return  QModelIndex();
    int rowNumber = rowForItem(parentItem);
    int colNumber = 0;
    return  createIndex(rowNumber,colNumber,parentItem);
}

int BP_GraphNodesModel::rowCount(const QModelIndex &parent) const
{
    BP_GraphNodeItem *parentNode = itemForIndex(parent);
    return parentNode->childItems.size();
}

int BP_GraphNodesModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant BP_GraphNodesModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role==Qt::DisplayRole)
    {
        if(index.column() == 0){
            BP_GraphNodeItem *importItem = itemForIndex(index);
            return  (importItem->coreObject() != nullptr ? importItem->coreObject()->name():importItem->m_displayName);
        }
        else if (index.column() == 1) {
            //connectedView->setIndexWidget(index,new QLabel("import"));
            return "";
        }
    }
    return QVariant();
}

BP_GraphNodeItem *BP_GraphNodesModel::rootItem() const
{
    return m_rootItem;
}

BP_Project *BP_GraphNodesModel::connectedProject() const
{
    return m_connectedProject;
}

void BP_GraphNodesModel::updateModule()
{
    //TODO add the new imported items instead of refreshing
    m_rootItem->clearChildes();

    //adding the imported library
    BP_GraphNodeItem *variablesItem = new BP_GraphNodeItem(m_rootItem,m_rootItem,"Imported Variables");
    foreach (BP_Variable* importedVar, m_connectedProject->importedVariables()) {
        BP_GraphNodeItem *varItem =new BP_GraphNodeItem(variablesItem,variablesItem);
        varItem->setCoreObject(importedVar);
    }

    BP_GraphNodeItem *classessItem = new BP_GraphNodeItem(m_rootItem,m_rootItem,"Imported Classes");
    foreach (auto class_, m_connectedProject->importedClasses()) {
        BP_GraphNodeItem *classItem = new BP_GraphNodeItem(classessItem,classessItem);
        classItem->setCoreObject(class_);
    }

    BP_GraphNodeItem *functionsItem = new BP_GraphNodeItem(m_rootItem,m_rootItem,"Imported Functions");
    foreach (auto function_, m_connectedProject->importedFunctions()) {
        BP_GraphNodeItem *functionItem = new BP_GraphNodeItem(functionsItem,functionsItem);
        functionItem->setCoreObject(function_);
    }

    foreach (auto module, m_connectedProject->importedModules()) {
        BP_GraphNodeItem *moduleItem = new BP_GraphNodeItem(m_rootItem,m_rootItem);
        moduleItem->setCoreObject(module);

        foreach (auto class_, module->classes()) {
            BP_GraphNodeItem *classItem = new BP_GraphNodeItem(moduleItem,moduleItem);
            classItem->setCoreObject(class_);
        }
        foreach (BP_Variable* variable, module->moduleValues()) {
            BP_GraphNodeItem *valueItem = new BP_GraphNodeItem(moduleItem,moduleItem);
            valueItem->setCoreObject(variable);
        }
        foreach (auto function_, module->functions()) {
            BP_GraphNodeItem *functionItem = new BP_GraphNodeItem(moduleItem,moduleItem);
            functionItem->setCoreObject(function_);
        }
    }
    emit layoutChanged();
}

void BP_GraphNodesModel::setRootItem(BP_GraphNodeItem *rootItem)
{
    if (m_rootItem == rootItem)
        return;

    m_rootItem = rootItem;
    emit rootItemChanged(m_rootItem);
}

void BP_GraphNodesModel::setConnectedProject(BP_Project *connectedProject)
{
    if (m_connectedProject == connectedProject)
        return;

    m_connectedProject = connectedProject;
    connect(m_connectedProject,&BP_Project::importedItemsAdded,this,&BP_GraphNodesModel::updateModule);
    emit connectedProjectChanged(m_connectedProject);
}
