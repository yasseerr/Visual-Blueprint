/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_MANAGERPROCESS_H
#define BP_MANAGERPROCESS_H

#include <QObject>
#include <QProcess>

class BP_ManagerProcess : public QProcess
{
    Q_OBJECT
public:
    BP_ManagerProcess();
};

#endif // BP_MANAGERPROCESS_H
