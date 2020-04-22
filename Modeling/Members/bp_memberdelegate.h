/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_MEMBERDELEGATE_H
#define BP_MEMBERDELEGATE_H

#include <QItemDelegate>
#include <QObject>
#include <QStyledItemDelegate>

#include <Core/bp_project.h>

class BP_MemberDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    BP_MemberDelegate(BP_Project *connectedProject);
    QStringList getProjectClasses() const;
    void changesCommited(QWidget *editor);

    BP_Project *m_connectedProject;
    // QAbstractItemDelegate interface
public:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    //virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // BP_MEMBERDELEGATE_H
