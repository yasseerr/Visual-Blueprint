/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "graphnodesselectiondialog.h"
#include "ui_graphnodesselectiondialog.h"

#include <QDebug>
#include <QFocusEvent>

GraphNodesSelectionDialog::GraphNodesSelectionDialog(BP_GraphNodesModel *graphNodesModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphNodesSelectionDialog),
    m_graphNodesModel(graphNodesModel)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Popup);

    //setWindowFlags(this->windowFlags()|Qt::Popup);
    m_graphProxyModel = new QSortFilterProxyModel(this);
    m_graphProxyModel->setFilterCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
    m_graphProxyModel->setSourceModel(m_graphNodesModel);
    m_graphProxyModel->setRecursiveFilteringEnabled(true);
    ui->nodesTreeView->setModel(m_graphProxyModel);
    ui->nodesTreeView->expandAll();
    //m_graphProxyModel.setfi
    connect(ui->lineEdit,&QLineEdit::textChanged,this,&GraphNodesSelectionDialog::selectionTextChanged);

}

GraphNodesSelectionDialog::~GraphNodesSelectionDialog()
{
    delete ui;
}

void GraphNodesSelectionDialog::selectionTextChanged(QString newText)
{
    m_graphProxyModel->setFilterFixedString(newText);
    ui->nodesTreeView->expandAll();
}

void GraphNodesSelectionDialog::focusOutEvent(QFocusEvent *event)
{
    QDialog::focusOutEvent(event);
    qDebug() << "focus out";
//    if(ui->lineEdit->hasFocus() || ui->nodesTreeView->hasFocus()) return;
//    this->reject();
}
