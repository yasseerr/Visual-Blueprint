/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_FLOWLINK_H
#define BP_FLOWLINK_H

#include "bp_link.h"

#include <QObject>

class BP_FlowLink : public BP_Link
{
    Q_OBJECT
public:
    BP_FlowLink(QObject *parent = nullptr);
};

#endif // BP_FLOWLINK_H
