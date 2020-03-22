/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "importsitemwidget.h"
#include "ui_importsitemwidget.h"

#include <QDebug>
#include <Modeling/importsmodel.h>

#include <Modeling/Imports/bp_importsmoduleitem.h>

ImportsItemWidget::ImportsItemWidget(BP_ImportsItem *importItem,BP_PlatformManager *platformManager,const QModelIndex widgetModelIndex,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportsItemWidget),
    m_widgetModelIndex(widgetModelIndex),
    m_importsItem(importItem),
    m_platformManager(platformManager)

{
    ui->setupUi(this);

    connect(ui->inspectToolButton,&QToolButton::clicked,this,&ImportsItemWidget::onInspectClicked);

}

ImportsItemWidget::~ImportsItemWidget()
{
    delete ui;
}

void ImportsItemWidget::onInspectClicked()
{
    qDebug() << "item Clicked" << m_importsItem->m_name;
    QList<QPair<QString,QString>> moduleMembers = m_platformManager->inspectModuleByName(m_importsItem->m_name);
    foreach (auto moduleMember, moduleMembers) {
        if(moduleMember.second == "module"){
            BP_ImportsModuleItem *moduleItem = new BP_ImportsModuleItem(moduleMember.first,m_importsItem,m_importsItem);
        }
    }
    if(m_importsItem->m_model != nullptr){
        m_importsItem->m_model->connectedView->setExpanded(m_widgetModelIndex,true);
        emit ((m_importsItem->m_model)->layoutChanged());
    }

}
