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

#include <Modeling/importsmodel.h>

class BP_CoreObject;

class BP_Utils : public QObject
{
    Q_OBJECT
public:
    enum MessageType{
        Info,Success,Warning,Error
    };
    Q_ENUM(MessageType)
    explicit BP_Utils(QObject *parent = nullptr);

    static BP_Utils* _instatce;

    static QTextEdit *textEdit;
    static void log(QString text,QString reference="",MessageType messageType=Info);
    static BP_Utils* instance();

public:
    ImportsModel *importsModel = nullptr;
    QMultiMap<QString,BP_CoreObject*> coreObjectsMap;


signals:

};

#endif // BP_UTILS_H
