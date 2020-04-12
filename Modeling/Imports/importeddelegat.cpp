/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "importeddelegat.h"

#include <QSpinBox>

#include <Widgets/importeddelegatewidget.h>

ImportedDelegat::ImportedDelegat():QItemDelegate()
{

}

QWidget *ImportedDelegat::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //open percistance editor
    ImportedDelegateWidget *editorWidget = new ImportedDelegateWidget(parent);
    return  editorWidget;
}

void ImportedDelegat::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    ImportedDelegateWidget *idw = static_cast<ImportedDelegateWidget*>(editor);
    idw->setImportedName(index.data().toString());
    idw->setImportedSourceModule(index.data(Qt::UserRole+1).toString());

}

void ImportedDelegat::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //QSpinBox *sb = static_cast<QSpinBox*>(editor);

}

void ImportedDelegat::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
