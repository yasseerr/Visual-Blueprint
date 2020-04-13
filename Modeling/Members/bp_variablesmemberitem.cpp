/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_variablesmemberitem.h"

#include <QDebug>
#include <QMenu>
#include <QPushButton>
#include "Modeling/Members/bp_membersmodel.h"

BP_VariablesMemberItem::BP_VariablesMemberItem(BP_MemberItem *parentItem,QObject *parent) : BP_MemberItem(parentItem,parent)
{
    setMemberName("Variables");

}

void BP_VariablesMemberItem::createVariablesMenu(const QList<QAction *> mainWindowAction)
{
    //creating the variables menu
    variablesToolBar = new QToolBar("variables");
    variablesToolBar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);

    //setting up the actions
    QStringList varsActionsNames;
    varsActionsNames << "Add Variable";
    variablesToolBar->addActions(mainWindowAction);
    variablesToolBar->setIconSize(QSize(15,15));
    variablesToolBar->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

    //variablesToolBar->setAutoFillBackground(true);
    //variablesToolBar->addAction("newAction");
    //variablesToolBar->show();
    if(m_model->m_connectedTreeView != nullptr){
        QModelIndex variablesIndex = m_model->widgetIndexForItem(this);
        m_model->m_connectedTreeView->setIndexWidget(variablesIndex,variablesToolBar);
    }
}
