/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_IMPORTSMODULEITEM_H
#define BP_IMPORTSMODULEITEM_H

#include "bp_importsitem.h"

#include <QObject>

class BP_ImportsModuleItem : public BP_ImportsItem
{
public:
    BP_ImportsModuleItem(QString name,BP_ImportsItem *parentItem,QObject *parent = nullptr);

    // BP_ImportsItem interface
public:
    virtual void importItem() override;
};

#endif // BP_IMPORTSMODULEITEM_H
