/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_FUNCTION_H
#define BP_FUNCTION_H

#include <QObject>

class BP_Function : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString functionName READ functionName WRITE setFunctionName NOTIFY functionNameChanged)

    QString m_functionName;

public:
    explicit BP_Function(QString _name,QObject *parent = nullptr);

    QString functionName() const;

public slots:
    void setFunctionName(QString functionName);

signals:

    void functionNameChanged(QString functionName);
};

#endif // BP_FUNCTION_H
