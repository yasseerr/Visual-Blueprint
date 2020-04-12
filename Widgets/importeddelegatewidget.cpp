/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "importeddelegatewidget.h"
#include "ui_importeddelegatewidget.h"

ImportedDelegateWidget::ImportedDelegateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportedDelegateWidget)
{
    ui->setupUi(this);
}

ImportedDelegateWidget::~ImportedDelegateWidget()
{
    delete ui;
}

QString ImportedDelegateWidget::importedName() const
{
    return m_importedName;
}

QString ImportedDelegateWidget::importedSourceModule() const
{
    return m_importedSourceModule;
}

void ImportedDelegateWidget::setImportedName(QString importedName)
{
    if (m_importedName == importedName)
        return;
    ui->nameLabel->setText(importedName);
    m_importedName = importedName;
    emit importedNameChanged(m_importedName);
}

void ImportedDelegateWidget::setImportedSourceModule(QString importedSourceModule)
{
    if (m_importedSourceModule == importedSourceModule)
        return;
     ui->hiearchylabel->setText(importedSourceModule);
    m_importedSourceModule = importedSourceModule;
    emit importedSourceModuleChanged(m_importedSourceModule);
}
