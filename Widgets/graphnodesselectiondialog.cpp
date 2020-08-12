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

#include <Graph/bp_graphview.h>
#include <Graph/bp_node.h>

GraphNodesSelectionDialog::GraphNodesSelectionDialog(BP_GraphNodesModel *graphNodesModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphNodesSelectionDialog),
    m_graphNodesModel(graphNodesModel),
    m_rootClass(nullptr),
    m_selfSlot(nullptr)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Popup);

    //setWindowFlags(this->windowFlags()|Qt::Popup);
    m_graphProxyModel = new QSortFilterProxyModel(this);
    m_graphProxyModel->setFilterCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
    m_graphProxyModel->setSourceModel(m_graphNodesModel);
    m_graphProxyModel->setRecursiveFilteringEnabled(true);
    //m_graphProxyModel->setDynamicSortFilter(true);
    ui->nodesTreeView->setModel(m_graphProxyModel);
    ui->nodesTreeView->expandAll();
    //m_graphProxyModel.setfi
    connect(ui->lineEdit,&QLineEdit::textChanged,this,&GraphNodesSelectionDialog::selectionTextChanged);
    connect(ui->nodesTreeView,&QTreeView::clicked,this,&GraphNodesSelectionDialog::graphTreeClickedEvent);
    connect(m_graphNodesModel,&BP_GraphNodesModel::contentChanged,this,&GraphNodesSelectionDialog::updateProxyModel);

}

GraphNodesSelectionDialog::~GraphNodesSelectionDialog()
{
    delete ui;
}

BP_Project *GraphNodesSelectionDialog::currentProject() const
{
    return m_currentProject;
}

BP_Class *GraphNodesSelectionDialog::rootClass() const
{
    return m_rootClass;
}

BP_Slot *GraphNodesSelectionDialog::selfSlot() const
{
    return m_selfSlot;
}

void GraphNodesSelectionDialog::selectionTextChanged(QString newText)
{
    m_graphProxyModel->setFilterRegExp(newText);
    emit m_graphProxyModel->layoutChanged();
    ui->nodesTreeView->expandAll();
}

void GraphNodesSelectionDialog::graphTreeClickedEvent(QModelIndex index)
{
    qDebug() << "item clicked : " << index.row();
    BP_GraphNodeItem *item = m_graphNodesModel->itemForIndex(m_graphProxyModel->mapToSource(index));
    if(!item->isTool() && item->coreObject() != nullptr){
        BP_Node *node = item->coreObject()->createNodeForObject(nullptr,m_currentProject->entryGraph());
        node->setCoreObject(item->coreObject());

        m_currentProject->entryGraph()->addNode(node,this->pos());

        //link the self slot
        if(m_selfSlot)node->connectSelfSlot(m_selfSlot);

    }
    else {
        BP_Node *node = item->createToolNode(m_currentProject->entryGraph());
        m_currentProject->entryGraph()->addNode(node,this->pos());
    }
    //thi is added to fix the bug when the model change and the selected item does not exist there anymore
    //ui->nodesTreeView->setCurrentIndex(m_graphNodesModel->indexForItem(m_graphNodesModel->rootItem()));
    ui->nodesTreeView->clearSelection();
    //ui->nodesTreeView->clearFocus();
    ui->nodesTreeView->setCurrentIndex(QModelIndex());
//    m_graphProxyModel->setFilterRegExp("");
    this->hide();

}

void GraphNodesSelectionDialog::updateProxyModel()
{
    emit m_graphProxyModel->layoutChanged();
    m_graphProxyModel->setSourceModel(m_graphNodesModel);
    //emit m_graphProxyModel->layoutChanged();
    //m_graphProxyModel->revert();
    //ui->nodesTreeView->update();
    //m_graphProxyModel->;
    //emit m_graphProxyModel->layoutChanged();
}

void GraphNodesSelectionDialog::setCurrentProject(BP_Project *currentProject)
{
    if (m_currentProject == currentProject)
        return;

    m_currentProject = currentProject;
    emit currentProjectChanged(m_currentProject);
}

void GraphNodesSelectionDialog::setRootClass(BP_Class *rootClass)
{
    if(rootClass){
        auto classNode = m_graphNodesModel->getCoreObjectNode(rootClass);
        if(!classNode) ui->nodesTreeView->setRootIndex(QModelIndex());
        auto classIndex = m_graphProxyModel->mapFromSource(m_graphNodesModel->indexForItem(classNode));
        ui->nodesTreeView->setRootIndex(classIndex);
        qDebug() << "root index changed";
    }else{
        ui->nodesTreeView->setRootIndex(QModelIndex());
    }
    if (m_rootClass == rootClass)
        return;

    m_rootClass = rootClass;

    emit m_graphProxyModel->layoutChanged();
    ui->nodesTreeView->update();
    ui->nodesTreeView->expandAll();
    emit rootClassChanged(m_rootClass);
}

void GraphNodesSelectionDialog::setSelfSlot(BP_Slot *selfSlot)
{
    if (m_selfSlot == selfSlot)
        return;

    m_selfSlot = selfSlot;
    emit selfSlotChanged(m_selfSlot);
}

void GraphNodesSelectionDialog::focusOutEvent(QFocusEvent *event)
{
    QDialog::focusOutEvent(event);
    qDebug() << "focus out";
    //    if(ui->lineEdit->hasFocus() || ui->nodesTreeView->hasFocus()) return;
    //    this->reject();
}

void GraphNodesSelectionDialog::focusInEvent(QFocusEvent *event)
{
    QDialog::focusInEvent(event);
    ui->lineEdit->setFocus();
}
