/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_MODULE_H
#define BP_MODULE_H

#include <QObject>

class BP_Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    QString m_name;

public:
    explicit BP_Module(QString name,QObject *parent = nullptr);
    QString name() const;

public slots:
    void setName(QString name);

signals:
    void nameChanged(QString name);
};

#endif // BP_MODULE_H
