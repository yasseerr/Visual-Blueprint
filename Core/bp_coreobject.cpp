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
#include "bp_module.h"

#include <Graph/bp_node.h>

BP_CoreObject::BP_CoreObject(QObject *parent) : QObject(parent)
{

}

QString BP_CoreObject::getImportSourceString()
{
    QString retString="";

    for (int i = m_importHiearchy.size()-1; i > 0  ; i--) {
        retString += m_importHiearchy.at(i);
        if(i!=1) retString += '.';
    }
    BP_Module *module = dynamic_cast<BP_Module*>(this);
    if(module != nullptr){
        if(m_importHiearchy.size()>1) retString += '.';
        retString += m_importHiearchy.at(0);
    }
    return  retString;
}

BP_Node *BP_CoreObject::createNodeForObject(QObject *parent)
{
    BP_Node *objectNode = new BP_Node(parent);
    objectNode->setCoreObject(this);
    return  objectNode;
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
