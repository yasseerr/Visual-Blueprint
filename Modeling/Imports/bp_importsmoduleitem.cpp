/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                    *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_importsmoduleitem.h"

#include <Modeling/importsmodel.h>

BP_ImportsModuleItem::BP_ImportsModuleItem(QString name,BP_ImportsItem *parentItem,QObject *parent):BP_ImportsItem(parentItem,parent)
{
    m_name = name;
}

void BP_ImportsModuleItem::importItem()
{
    BP_ImportsItem::importItem();
    m_model->connectedProject()->importModule(getImportHierarchy());
}
