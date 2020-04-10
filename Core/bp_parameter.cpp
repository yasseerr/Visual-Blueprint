/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_parameter.h"

BP_Parameter::BP_Parameter(QObject *parent) : QObject(parent)
{

}

QString BP_Parameter::parameterName() const
{
    return m_parameterName;
}

BP_Class *BP_Parameter::parameterClass() const
{
    return m_parameterClass;
}

BP_Variable *BP_Parameter::defualtValue() const
{
    return m_defualtValue;
}

BP_Parameter::Kind BP_Parameter::kind() const
{
    return m_kind;
}

void BP_Parameter::setParameterName(QString parameterName)
{
    if (m_parameterName == parameterName)
        return;

    m_parameterName = parameterName;
    emit parameterNameChanged(m_parameterName);
}

void BP_Parameter::setParameterClass(BP_Class *parameterClass)
{
    if (m_parameterClass == parameterClass)
        return;

    m_parameterClass = parameterClass;
    emit parameterClassChanged(m_parameterClass);
}

void BP_Parameter::setDefualtValue(BP_Variable *defualtValue)
{
    if (m_defualtValue == defualtValue)
        return;

    m_defualtValue = defualtValue;
    emit defualtValueChanged(m_defualtValue);
}

void BP_Parameter::setKind(BP_Parameter::Kind kind)
{
    if (m_kind == kind)
        return;

    m_kind = kind;
    emit kindChanged(m_kind);
}
