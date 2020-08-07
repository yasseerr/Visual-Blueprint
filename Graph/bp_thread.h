/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_THREAD_H
#define BP_THREAD_H

#include <QColor>
#include <QObject>
#include <QSet>

class BP_Node;
class BP_Slot;

class BP_Thread : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int threadID READ threadID WRITE setThreadID NOTIFY threadIDChanged)
    Q_PROPERTY(QColor threadColor READ threadColor WRITE setThreadColor NOTIFY threadColorChanged)
    Q_PROPERTY(QSet<BP_Slot*> sharedRefsSlots READ sharedRefsSlots WRITE setSharedRefsSlots NOTIFY sharedRefsSlotsChanged)
    //Q_PROPERTY(QList<BP_Node*> sharedNodes READ sharedNodes WRITE setSharedNodes NOTIFY sharedNodesChanged)

    int m_threadID;

    static int threadsCount;

    QColor m_threadColor;

    //QList<BP_Node*> m_sharedNodes;

    QSet<BP_Slot*> m_sharedRefsSlots;

public:
    explicit BP_Thread(QObject *parent = nullptr);

    int threadID() const;

    QColor threadColor() const;

    //QList<BP_Node*> sharedNodes() const;

    QSet<BP_Slot*> sharedRefsSlots();

public slots:
    void setThreadID(int threadID);

    void setThreadColor(QColor threadColor);

    //void setSharedNodes(QList<BP_Node*> sharedNodes);

    void setSharedRefsSlots(QSet<BP_Slot*> sharedRefsSlots);

signals:

    void threadIDChanged(int threadID);
    void threadColorChanged(QColor threadColor);
    //void sharedNodesChanged(QList<BP_Node*> sharedNodes);
    void sharedRefsSlotsChanged(QSet<BP_Slot*> sharedRefsSlots);
};

#endif // BP_THREAD_H
