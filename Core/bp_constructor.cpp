/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_constructor.h"
#include "bp_parameter.h"

BP_Constructor::BP_Constructor(QVariantMap *variableMap,QObject *parent) : QObject(parent),
    m_constructorId(-1),
    m_hasKeyWords(false),
    m_hasPositional(false)
{
    if(variableMap != nullptr){
        m_hasKeyWords = variableMap->value("hasKeyWords").toBool();
        m_hasPositional = variableMap->value("hasPositional").toBool();

        //adding the parameters
        foreach (auto inputVariant, variableMap->value("inputs").toList()) {
            QVariantMap parameterVariant = inputVariant.toMap();
            BP_Parameter *param = new BP_Parameter(this,&parameterVariant);
            m_inputs << param;
        }
    }

}

int BP_Constructor::constructorId() const
{
    return m_constructorId;
}

QList<BP_Parameter *> BP_Constructor::inputs() const
{
    return m_inputs;
}

bool BP_Constructor::hasKeyWords() const
{
    return m_hasKeyWords;
}

bool BP_Constructor::hasPositional() const
{
    return m_hasPositional;
}

void BP_Constructor::setConstructorId(int constructorId)
{
    if (m_constructorId == constructorId)
        return;

    m_constructorId = constructorId;
    emit constructorIdChanged(m_constructorId);
}

void BP_Constructor::setInputs(QList<BP_Parameter *> inputs)
{
    if (m_inputs == inputs)
        return;

    m_inputs = inputs;
    emit inputsChanged(m_inputs);
}

void BP_Constructor::setHasKeyWords(bool hasKeyWords)
{
    if (m_hasKeyWords == hasKeyWords)
        return;

    m_hasKeyWords = hasKeyWords;
    emit hasKeyWordsChanged(m_hasKeyWords);
}

void BP_Constructor::setHasPositional(bool hasPositional)
{
    if (m_hasPositional == hasPositional)
        return;

    m_hasPositional = hasPositional;
    emit hasPositionalChanged(m_hasPositional);
}
