/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_PROJECT_H
#define BP_PROJECT_H

#include <QObject>

class BP_Project : public QObject
{
    Q_OBJECT
public:
    explicit BP_Project(QObject *parent = nullptr);

signals:

};

#endif // BP_PROJECT_H
