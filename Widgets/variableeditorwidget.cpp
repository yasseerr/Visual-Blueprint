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

#include <QAbstractItemView>
#include <QDebug>
#include <QStringListModel>

VariableEditorWidget::VariableEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VariableEditorWidget),
    classesModel(new QStringListModel(this))
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
    ui->comboBox->view()->setMinimumWidth(100);

    connect(ui->toolButton,&QToolButton::clicked,this,&VariableEditorWidget::onConfirmClicked);
}

VariableEditorWidget::~VariableEditorWidget()
{
    delete ui;
}

void VariableEditorWidget::setEditorData(QString className, int multiplicityIndex)
{
    //ui->lineEdit->setText(className);
    ui->comboBox->setCurrentIndex(multiplicityIndex);
    ui->classComboBox->setCurrentText(className);
}

void VariableEditorWidget::setComboModel(QStringList classesList)
{
    classesModel->setStringList(classesList);
    ui->classComboBox->setModel(classesModel);
    ui->classComboBox->view()->setMinimumWidth(calculateClassesDropDownWidth(classesList));
}

int VariableEditorWidget::calculateClassesDropDownWidth(QStringList classesList)
{
    int maxLenght = 0;
    foreach (QString className, classesList) {
       int classNameWidth = ui->classComboBox->fontMetrics().boundingRect(className).width();
       if(classNameWidth > maxLenght)
           maxLenght = classNameWidth;
    }
    return  maxLenght;
}

QString VariableEditorWidget::getClassName()
{
    return ui->classComboBox->currentText();
}

int VariableEditorWidget::getMultiplictyIndex()
{
    return  ui->comboBox->currentIndex();
}

void VariableEditorWidget::onConfirmClicked()
{
    qDebug() << "confirmed";
    emit changeCommited(this);
}
