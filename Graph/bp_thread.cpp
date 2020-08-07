/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_slot.h"
#include "bp_thread.h"

#include <QRandomGenerator>

int BP_Thread::threadsCount = 0;

BP_Thread::BP_Thread(QObject *parent) : QObject(parent),
    m_threadID(threadsCount),
    m_threadColor(QColor::fromRgb(QRandomGenerator::global()->generate()))
{
    threadsCount++;
}

int BP_Thread::threadID() const
{
    return m_threadID;
}

QColor BP_Thread::threadColor() const
{
    return m_threadColor;
}

QSet<BP_Slot *> BP_Thread::sharedRefsSlots()
{
    return m_sharedRefsSlots;
}

//QList<BP_Node *> BP_Thread::sharedNodes() const
//{
//    return m_sharedNodes;
//}

void BP_Thread::setThreadID(int threadID)
{
    if (m_threadID == threadID)
        return;

    m_threadID = threadID;
    emit threadIDChanged(m_threadID);
}

void BP_Thread::setThreadColor(QColor threadColor)
{
    if (m_threadColor == threadColor)
        return;

    m_threadColor = threadColor;
    emit threadColorChanged(m_threadColor);
}

void BP_Thread::setSharedRefsSlots(QSet<BP_Slot *> sharedRefsSlots)
{
    if (m_sharedRefsSlots == sharedRefsSlots)
        return;

    m_sharedRefsSlots = sharedRefsSlots;
    emit sharedRefsSlotsChanged(m_sharedRefsSlots);
}

//void BP_Thread::setSharedNodes(QList<BP_Node *> sharedNodes)
//{
//    if (m_sharedNodes == sharedNodes)
//        return;

//    m_sharedNodes = sharedNodes;
//    emit sharedNodesChanged(m_sharedNodes);
//}
