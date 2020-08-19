/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_ASYNC_H
#define BP_ASYNC_H

#include <QObject>
#include <QSet>

class BP_Slot;

class BP_Async : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int asyncID READ asyncID WRITE setAsyncID NOTIFY asyncIDChanged)
    Q_PROPERTY(QSet<BP_Slot*> sharedRefsSlots READ sharedRefsSlots WRITE setSharedRefsSlots NOTIFY sharedRefsSlotsChanged)

    static int asyncCount;

    int m_asyncID;

public:
    QSet<BP_Slot*> m_sharedRefsSlots;


public:
    explicit BP_Async(QObject *parent = nullptr);

    int asyncID() const;

    QSet<BP_Slot*> sharedRefsSlots() const;

public slots:
    void setAsyncID(int asyncID);

    void setSharedRefsSlots(QSet<BP_Slot*> sharedRefsSlots);

signals:
    void asyncIDChanged(int asyncID);
    void sharedRefsSlotsChanged(QSet<BP_Slot*> sharedRefsSlots);
};

#endif // BP_ASYNC_H
