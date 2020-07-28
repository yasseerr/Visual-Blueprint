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

class BP_Thread : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int threadID READ threadID WRITE setThreadID NOTIFY threadIDChanged)
    Q_PROPERTY(QColor threadColor READ threadColor WRITE setThreadColor NOTIFY threadColorChanged)

    int m_threadID;

    static int threadsCount;

    QColor m_threadColor;

public:
    explicit BP_Thread(QObject *parent = nullptr);

    int threadID() const;

    QColor threadColor() const;

public slots:
    void setThreadID(int threadID);

    void setThreadColor(QColor threadColor);

signals:

    void threadIDChanged(int threadID);
    void threadColorChanged(QColor threadColor);
};

#endif // BP_THREAD_H
