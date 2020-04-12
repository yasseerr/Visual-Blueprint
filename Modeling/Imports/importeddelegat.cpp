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

ImportedDelegat::ImportedDelegat():QItemDelegate()
{

}

QWidget *ImportedDelegat::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *spinBoxDelegate = new QSpinBox(parent);
    return  spinBoxDelegate;
}

void ImportedDelegat::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QSpinBox *sb = static_cast<QSpinBox*>(editor);
    sb->setValue(20);
}

void ImportedDelegat::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *sb = static_cast<QSpinBox*>(editor);

}

void ImportedDelegat::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
