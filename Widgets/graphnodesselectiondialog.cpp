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

GraphNodesSelectionDialog::GraphNodesSelectionDialog(BP_GraphNodesModel *graphNodesModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphNodesSelectionDialog),
    m_graphNodesModel(graphNodesModel)
{
    ui->setupUi(this);

    m_graphProxyModel = new QSortFilterProxyModel(this);
    m_graphProxyModel->setFilterCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
    m_graphProxyModel->setSourceModel(m_graphNodesModel);
    m_graphProxyModel->setRecursiveFilteringEnabled(true);
    ui->nodesTreeView->setModel(m_graphProxyModel);
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
}
