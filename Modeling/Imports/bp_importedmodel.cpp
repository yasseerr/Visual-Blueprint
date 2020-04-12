/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_importedmodel.h"

#include <Core/bp_project.h>

BP_ImportedModel::BP_ImportedModel():
    m_project(nullptr)
{

}

int BP_ImportedModel::rowCount(const QModelIndex &parent) const
{
    return m_importedList.size();
}

QVariant BP_ImportedModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();
    if(index.column() == 0){
        if(role == Qt::DisplayRole) return m_importedList.at(index.row())->name();
    }
    return QVariant();
}

BP_Project *BP_ImportedModel::project() const
{
    return m_project;
}

QList<BP_CoreObject *> BP_ImportedModel::importedList() const
{
    return m_importedList;
}

void BP_ImportedModel::setProject(BP_Project *project)
{
    if (m_project == project)
        return;
    connect(project,&BP_Project::importedItemsAdded,this,&BP_ImportedModel::addImportedObject);
    m_project = project;
    emit projectChanged(m_project);
}

void BP_ImportedModel::setImportedList(QList<BP_CoreObject *> importedList)
{
    if (m_importedList == importedList)
        return;
    m_importedList = importedList;
    emit importedListChanged(m_importedList);
}

void BP_ImportedModel::addImportedObject(BP_CoreObject *importedObj)
{
    m_importedList << importedObj;

    emit layoutChanged();
}


