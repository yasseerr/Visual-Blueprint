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

#include <bp_utils.h>

BP_CoreObject::BP_CoreObject(QObject *parent) : QObject(parent),m_isImported(true),m_isProjectMember(false)
{

}

QVariant BP_CoreObject::toVariantBP()
{
    /* the nodes will be saved as follow
     * Variables : member variables -> store the value directly from the 'variableValue' without using the hierarchy
     *             imported variables-> create an instance after searching for the variable using the name and hierarchy
     *              primitive variables -> store the value only
     * Classes : only referencing using name and hierarchy
     * functions: members -> store value only
     *            imported -> serch using the reference or module
    */
    QVariantMap retMap;
    retMap["name"] = m_name;
    retMap["importHierarcht"] = QVariant::fromValue(m_importHiearchy);
    retMap["isImported"] = m_isImported;
    retMap["isProjectMember"] = m_isProjectMember;
    //? the threads are automaticly loaded in BP_DataSlot::acceptConnection
    return retMap;
    //return "a core object";

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

bool BP_CoreObject::isImported() const
{
    return m_isImported;
}

bool BP_CoreObject::isProjectMember() const
{
    return m_isProjectMember;
}

QSet<BP_FrameBranch *> BP_CoreObject::connectedBranches()
{
    return m_connectedBranches;
}

void BP_CoreObject::setName(QString name)
{
    if (m_name == name)
        return;
    //save the name in the names map
    BP_Utils::instance()->coreObjectsMap.insert(name,this);

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

void BP_CoreObject::setIsImported(bool isImported)
{
    if (m_isImported == isImported)
        return;

    m_isImported = isImported;
    emit isImportedChanged(m_isImported);
}

void BP_CoreObject::setIsProjectMember(bool isProjectMember)
{
    if (m_isProjectMember == isProjectMember)
        return;

    m_isProjectMember = isProjectMember;
    emit isProjectMemberChanged(m_isProjectMember);
}

void BP_CoreObject::setConnectedBranches(QSet<BP_FrameBranch *> connectedBranches)
{
    if (m_connectedBranches == connectedBranches)
        return;

    m_connectedBranches = connectedBranches;
    emit connectedBranchesChanged(m_connectedBranches);
}
