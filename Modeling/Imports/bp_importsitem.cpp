/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_importsitem.h"

BP_ImportsItem::BP_ImportsItem(BP_ImportsItem *parentItem,QObject *parent) : QObject(parent),
  m_parentItem(parentItem)
{
    if(m_parentItem != nullptr)
        m_parentItem->childItems.append(this);

}
