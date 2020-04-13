/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "variableeditorwidget.h"
#include "ui_variableeditorwidget.h"

VariableEditorWidget::VariableEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VariableEditorWidget)
{
    ui->setupUi(this);
    multiplicityModel = new QStandardItemModel(this);
    QStandardItem *scalarItem  = new QStandardItem("variable");
    scalarItem->setIcon(QIcon(":/Data/Images/DefaultIcon/3D-Cube.png"));
    QStandardItem *listItem  = new QStandardItem("list");
    listItem->setIcon(QIcon(":/Data/Images/DefaultIcon/list.png"));
    QStandardItem *matrixItem  = new QStandardItem("matrix");
    matrixItem->setIcon(QIcon(":/Data/Images/DefaultIcon/grid.png"));
    multiplicityModel->appendRow(scalarItem);
    multiplicityModel->appendRow(listItem);
    multiplicityModel->appendRow(matrixItem);
    ui->comboBox->setModel(multiplicityModel);
}

VariableEditorWidget::~VariableEditorWidget()
{
    delete ui;
}
