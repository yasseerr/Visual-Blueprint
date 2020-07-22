/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_utils.h"

QTextEdit* BP_Utils::textEdit  = nullptr;
BP_Utils* BP_Utils::_instatce = new BP_Utils();

BP_Utils::BP_Utils(QObject *parent) : QObject(parent)
{

}

void BP_Utils::log(QString text,QString reference,MessageType messageType)
{
    QMap<MessageType,QString> messageColors;
    messageColors.insert(MessageType::Info,"#888888");
    messageColors.insert(MessageType::Success,"#55B83B");
    messageColors.insert(MessageType::Warning,"#ffff00");
    messageColors.insert(MessageType::Error,"#ff0000");
    QString displayText = "<div><span style='color:" + messageColors.value(messageType,"#000000") +"'>#" +
            QVariant::fromValue(messageType).toString() +"::"+reference+"</span> "+  text + "</div>";
    textEdit->append(displayText);
}

void BP_Utils::logPlainText(QString text)
{
    textEdit->moveCursor(QTextCursor::End);
    textEdit->insertPlainText(text);
}

BP_Utils *BP_Utils::instance()
{
    if(!_instatce) _instatce = new BP_Utils();

    return _instatce;

}
