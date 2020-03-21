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

ImportsItemWidget::ImportsItemWidget(BP_ImportsItem *importItem,const QModelIndex widgetModelIndex,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportsItemWidget),
    m_widgetModelIndex(widgetModelIndex),
    m_importsItem(importItem)

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
}
