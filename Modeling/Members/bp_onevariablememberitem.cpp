/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_onevariablememberitem.h"

#include <QDebug>
#include <QIcon>
#include <QVariant>

BP_OneVariableMemberItem::BP_OneVariableMemberItem(BP_MemberItem *parentItem,QObject *parent) : BP_MemberItem(parentItem,parent)
{
    setMemberName("NewVariable");
    connect(this,&BP_OneVariableMemberItem::memberNameChanged,this,&BP_OneVariableMemberItem::updateMemberName);
}

BP_Variable *BP_OneVariableMemberItem::containedVariable() const
{
    return m_containedVariable;
}

void BP_OneVariableMemberItem::setContainedVariable(BP_Variable *containedVariable)
{
    if (m_containedVariable == containedVariable)
        return;

    m_containedVariable = containedVariable;
    emit containedVariableChanged(m_containedVariable);
}

void BP_OneVariableMemberItem::updateMemberName()
{
    //when the name changed in the model propagate the change to the BP_Varible
    m_containedVariable->setName(memberName());
    qDebug() << "Variable Name Changed: " << m_containedVariable->name();
}

QVariant BP_OneVariableMemberItem::getDesctiptionData(int role)
{
    if(role == Qt::DecorationRole){
        if(m_containedVariable->isArray())
            return QVariant::fromValue(QIcon(":/Data/Images/DefaultIcon/list.png"));
        else {
            return QVariant::fromValue(QIcon(":/Data/Images/DefaultIcon/3D-Cube.png"));
        }
    }
    else if (role == Qt::DisplayRole) {
        return m_containedVariable->className();
    }
    else if (role == Qt::UserRole+1){

        return m_containedVariable->isArray()?1:0;
    }
    else return  QVariant();
}

bool BP_OneVariableMemberItem::setDescriptionData(QVariant data, int role)
{
    if(role == Qt::EditRole){
        //TODO add the class hierarchy
        m_containedVariable->setIsProjectMember(true);
        m_containedVariable->setClassName(data.toMap().value("className").toString());
        m_containedVariable->setIsArray((data.toMap().value("multiplicity").toInt()==0?false:true));
        return true;
    }
    else{
        return false;
    }
}
