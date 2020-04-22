/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_DATASLOT_H
#define BP_DATASLOT_H

#include <QObject>

#include <Graph/bp_slot.h>

class BP_DataSlot : public BP_Slot
{
    Q_OBJECT
public:
    BP_DataSlot(QObject *parent = nullptr);
};

#endif // BP_DATASLOT_H
