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

BP_ImportsModuleItem::BP_ImportsModuleItem(QString name,BP_ImportsItem *parentItem,QObject *parent):BP_ImportsItem(parentItem,parent)
{
    m_name = name;
}
