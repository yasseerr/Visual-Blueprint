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

BP_ImportedModel::BP_ImportedModel():
    m_project(nullptr)
{

}

int BP_ImportedModel::rowCount(const QModelIndex &parent) const
{

}

QVariant BP_ImportedModel::data(const QModelIndex &index, int role) const
{

}

BP_Project *BP_ImportedModel::project() const
{
    return m_project;
}

void BP_ImportedModel::setProject(BP_Project *project)
{
    if (m_project == project)
        return;

    m_project = project;
    emit projectChanged(m_project);
}
