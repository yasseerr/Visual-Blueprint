/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_variable.h"

BP_Variable::BP_Variable(QObject *parent) : QObject(parent)
{

}

QString BP_Variable::variableName() const
{
    return m_variableName;
}

bool BP_Variable::isPrimitive() const
{
    return m_isPrimitive;
}

void BP_Variable::setVariableName(QString variableName)
{
    if (m_variableName == variableName)
        return;

    m_variableName = variableName;
    emit variableNameChanged(m_variableName);
}

void BP_Variable::setIsPrimitive(bool isPrimitive)
{
    if (m_isPrimitive == isPrimitive)
        return;

    m_isPrimitive = isPrimitive;
    emit isPrimitiveChanged(m_isPrimitive);
}
