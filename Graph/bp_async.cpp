/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_async.h"

int BP_Async::asyncCount = 0;

BP_Async::BP_Async(QObject *parent) : QObject(parent),
    m_asyncID(asyncCount)
{

}

int BP_Async::asyncID() const
{
    return m_asyncID;
}

QSet<BP_Slot *> BP_Async::sharedRefsSlots() const
{
    return m_sharedRefsSlots;
}

void BP_Async::setAsyncID(int asyncID)
{
    if (m_asyncID == asyncID)
        return;

    m_asyncID = asyncID;
    emit asyncIDChanged(m_asyncID);
}

void BP_Async::setSharedRefsSlots(QSet<BP_Slot *> sharedRefsSlots)
{
    if (m_sharedRefsSlots == sharedRefsSlots)
        return;

    m_sharedRefsSlots = sharedRefsSlots;
    emit sharedRefsSlotsChanged(m_sharedRefsSlots);
}
