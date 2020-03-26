/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_importsitem.h"

#include <Modeling/importsmodel.h>

#include <QDebug>

BP_ImportsItem::BP_ImportsItem(BP_ImportsItem *parentItem,QObject *parent) : QObject(parent),
  m_parentItem(parentItem),m_importable(true),m_isExpanded(false),m_isInspectable(true)
{
    if(m_parentItem != nullptr){
        m_parentItem->childItems.append(this);
        if(m_parentItem->m_model != nullptr)
            m_model = m_parentItem->m_model;
    }

}

QStringList BP_ImportsItem::getImportHierarchy()
{
    QStringList retList;
    BP_ImportsItem *hierarchtStep = this;
    while (hierarchtStep != nullptr) {
        retList << hierarchtStep->m_name;
        hierarchtStep = hierarchtStep->m_parentItem;
        if(hierarchtStep == m_model->rootItem())
            break;
    }
    return  retList;
}

QVariant BP_ImportsItem::getIconVariant()
{
    QIcon itemIcon(":/Data/Images/DefaultIcon/hardware-processor.png");
    return QVariant::fromValue(itemIcon);
}

void BP_ImportsItem::importItem()
{
    qDebug() << "No imports for abstract imports item";
}

bool BP_ImportsItem::importable() const
{
    return m_importable;
}

bool BP_ImportsItem::isExpanded() const
{
    return m_isExpanded;
}

bool BP_ImportsItem::isInspectable() const
{
    return m_isInspectable;
}

void BP_ImportsItem::setImportable(bool importable)
{
    if (m_importable == importable)
        return;

    m_importable = importable;
    emit importableChanged(m_importable);
}

void BP_ImportsItem::setIsExpanded(bool isExpanded)
{
    if (m_isExpanded == isExpanded)
        return;

    m_isExpanded = isExpanded;
    emit isExpandedChanged(m_isExpanded);
}

void BP_ImportsItem::setIsInspectable(bool isInspectable)
{
    if (m_isInspectable == isInspectable)
        return;

    m_isInspectable = isInspectable;
    emit isInspectableChanged(m_isInspectable);
}
