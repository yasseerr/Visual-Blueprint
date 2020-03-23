/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_IMPORTSFUNCTIONITEM_H
#define BP_IMPORTSFUNCTIONITEM_H

#include "bp_importsitem.h"

#include <QObject>

class BP_ImportsFunctionItem : public BP_ImportsItem
{
    Q_OBJECT
public:
    explicit BP_ImportsFunctionItem(QString _name,BP_ImportsItem *parentItem,QObject *parent = nullptr);

    // BP_ImportsItem interface
public:
    virtual QVariant getIconVariant() override;
};

#endif // BP_IMPORTSFUNCTIONITEM_H
