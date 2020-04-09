/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_CLASS_H
#define BP_CLASS_H

#include <QObject>

class BP_Class : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString className READ className WRITE setClassName NOTIFY classNameChanged)
    QString m_className;

public:
    explicit BP_Class(QObject *parent = nullptr);

    QString className() const;

public slots:
    void setClassName(QString className);

signals:

    void classNameChanged(QString className);
};

#endif // BP_CLASS_H
