/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_coreobject.h"

BP_CoreObject::BP_CoreObject(QObject *parent) : QObject(parent)
{

}

QString BP_CoreObject::name() const
{
    return m_name;
}

QStringList BP_CoreObject::importHiearchy() const
{
    return m_importHiearchy;
}

void BP_CoreObject::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void BP_CoreObject::setImportHiearchy(QStringList importHiearchy)
{
    if (m_importHiearchy == importHiearchy)
        return;

    m_importHiearchy = importHiearchy;
    emit importHiearchyChanged(m_importHiearchy);
}
