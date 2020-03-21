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

ImportsItemWidget::ImportsItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportsItemWidget)
{
    ui->setupUi(this);
}

ImportsItemWidget::~ImportsItemWidget()
{
    delete ui;
}
