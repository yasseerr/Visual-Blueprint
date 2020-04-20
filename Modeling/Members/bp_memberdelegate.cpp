/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_memberdelegate.h"

#include <Widgets/variableeditorwidget.h>

#include <Core/bp_class.h>
#include <Core/bp_module.h>

BP_MemberDelegate::BP_MemberDelegate(BP_Project *connectedProject):m_connectedProject(connectedProject)
{

}

QWidget *BP_MemberDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return  new VariableEditorWidget(parent);
}

void BP_MemberDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    VariableEditorWidget *varEdit = static_cast<VariableEditorWidget*>(editor);
    varEdit->setEditorData(index.data().toString(),index.data(Qt::UserRole+1).toInt());
    QStringList projectClasses =  getProjectClasses();
    varEdit->setComboModel(projectClasses);
    connect(varEdit,&VariableEditorWidget::changeCommited,this,&BP_MemberDelegate::changesCommited);
}

void BP_MemberDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    VariableEditorWidget *varEdit = static_cast<VariableEditorWidget*>(editor);
    QVariantMap dataMap;
    dataMap.insert("className",varEdit->getClassName());
    dataMap.insert("multiplicity",varEdit->getMultiplictyIndex());
    model->setData(index,dataMap);

}

void BP_MemberDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
QStringList BP_MemberDelegate::getProjectClasses() const
{
    QStringList retList;
    foreach(BP_Class *bp_class, m_connectedProject->importedClasses()) {
        retList << bp_class->name();
    }
    foreach (BP_Module *module, m_connectedProject->importedModules()) {
        foreach(BP_Class *bp_class, module->classes()) {
            retList << bp_class->name();
        }
    }
    return  retList;
}

void BP_MemberDelegate::changesCommited(QWidget *editor)
{
    emit commitData(editor);
    emit closeEditor(editor);
}
