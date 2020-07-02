/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_UTILS_H
#define BP_UTILS_H

#include <QObject>
#include <QTextEdit>

class BP_Utils : public QObject
{
    Q_OBJECT
public:
    enum MessageType{
        Info,Success,Warning,Error
    };
    Q_ENUM(MessageType)
    explicit BP_Utils(QObject *parent = nullptr);

    static QTextEdit *textEdit;
    static void log(QString text,QString reference="",MessageType messageType=Info);

signals:

};

#endif // BP_UTILS_H