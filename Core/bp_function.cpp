/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_function.h"

BP_Function::BP_Function(QString _name,QObject *parent) : QObject(parent),m_functionName(_name)
{

}

QString BP_Function::functionName() const
{
    return m_functionName;
}

void BP_Function::setFunctionName(QString functionName)
{
    if (m_functionName == functionName)
        return;

    m_functionName = functionName;
    emit functionNameChanged(m_functionName);
}
