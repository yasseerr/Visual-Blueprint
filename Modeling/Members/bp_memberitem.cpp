/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_memberitem.h"

#include <QVariant>

BP_MemberItem::BP_MemberItem(BP_MemberItem *parentItem,QObject *parent) : QObject(parent),m_parentItem(parentItem),m_memberName("")
{
    if(m_parentItem != nullptr){
        m_parentItem->childItems.append(this);
        if(m_parentItem->m_model != nullptr)
            m_model = m_parentItem->m_model;
    }
}

QString BP_MemberItem::memberName() const
{
    return m_memberName;
}

QVariant BP_MemberItem::getDesctiptionData(int role)
{
    if(role == Qt::DisplayRole)
        return "";
    else
        return  QVariant();
}

bool BP_MemberItem::setDescriptionData(QVariant data, int role)
{
    return false;
}

void BP_MemberItem::setMemberName(QString memberName)
{
    if (m_memberName == memberName)
        return;

    m_memberName = memberName;
    emit memberNameChanged(m_memberName);
}
