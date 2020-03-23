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

#include <Modeling/Imports/bp_importsfunctionitem.h>
#include <Modeling/Imports/bp_importsmoduleitem.h>

ImportsItemWidget::ImportsItemWidget(BP_ImportsItem *importItem,BP_PlatformManager *platformManager,const QModelIndex widgetModelIndex,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportsItemWidget),
    m_widgetModelIndex(widgetModelIndex),
    m_importsItem(importItem),
    m_platformManager(platformManager)

{
    ui->setupUi(this);
    ui->inspectToolButton->setVisible(importItem->isInspectable());
    connect(ui->inspectToolButton,&QToolButton::clicked,this,&ImportsItemWidget::onInspectClicked);

}

ImportsItemWidget::~ImportsItemWidget()
{
    delete ui;
}

void ImportsItemWidget::onInspectClicked()
{
    if(m_importsItem->isExpanded()) return;
    qDebug() << "item Clicked" << m_importsItem->m_name << " " <<m_importsItem->getImportHierarchy();
    QList<QPair<QString,QString>> moduleMembers = m_platformManager->inspectModuleByName(m_importsItem->getImportHierarchy());
    //adding the modules first
    foreach (auto moduleMember, moduleMembers) {
        if(moduleMember.second == "module"){
            BP_ImportsModuleItem *moduleItem = new BP_ImportsModuleItem(moduleMember.first,m_importsItem,m_importsItem);
            m_importsItem->m_model->setupItemWidget(moduleItem,m_platformManager);
        }

    }
    foreach (auto moduleMember, moduleMembers) {
        if(moduleMember.second == "function"){
            BP_ImportsFunctionItem *functionItem = new BP_ImportsFunctionItem(moduleMember.first,m_importsItem,m_importsItem);
            m_importsItem->m_model->setupItemWidget(functionItem,m_platformManager);
        }
    }
    if(m_importsItem->m_model != nullptr){
        m_importsItem->m_model->connectedView->setExpanded(m_widgetModelIndex,true);
        emit ((m_importsItem->m_model)->layoutChanged());
    }
    m_importsItem->setIsExpanded(true);
    ui->inspectToolButton->setEnabled(false);
    ui->inspectToolButton->setIcon(QIcon(":/Data/Images/DefaultIcon/MD-stop.png"));

}

void ImportsItemWidget::onExpandedChanged()
{

}
