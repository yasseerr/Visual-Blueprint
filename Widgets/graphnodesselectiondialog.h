/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef GRAPHNODESSELECTIONDIALOG_H
#define GRAPHNODESSELECTIONDIALOG_H

#include <QDialog>
#include <QSortFilterProxyModel>

#include <Modeling/Graph/bp_graphnodesmodel.h>
#include <QAbstractProxyModel>
class BP_Slot;

namespace Ui {
class GraphNodesSelectionDialog;
}

class GraphNodesSelectionDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(BP_Project* currentProject READ currentProject WRITE setCurrentProject NOTIFY currentProjectChanged)
    Q_PROPERTY(BP_Class* rootClass READ rootClass WRITE setRootClass NOTIFY rootClassChanged)
    Q_PROPERTY(BP_Slot* selfSlot READ selfSlot WRITE setSelfSlot NOTIFY selfSlotChanged)

public:
    explicit GraphNodesSelectionDialog(BP_GraphNodesModel *graphNodesModel,QWidget *parent = nullptr);
    ~GraphNodesSelectionDialog();

    BP_Project* currentProject() const;

    BP_Class* rootClass() const;

    BP_Slot* selfSlot() const;

public slots:
    void selectionTextChanged(QString newText);
    void graphTreeClickedEvent(QModelIndex index);
    void updateProxyModel();

    void setCurrentProject(BP_Project* currentProject);

    void setRootClass(BP_Class* rootClass);

    void setSelfSlot(BP_Slot* selfSlot);

signals:
    void currentProjectChanged(BP_Project* currentProject);

    void rootClassChanged(BP_Class* rootClass);

    void selfSlotChanged(BP_Slot* selfSlot);

private:
    Ui::GraphNodesSelectionDialog *ui;
    BP_GraphNodesModel *m_graphNodesModel;
    QSortFilterProxyModel *m_graphProxyModel;


    // QWidget interface
    BP_Project* m_currentProject;

    BP_Class* m_rootClass;

    BP_Slot* m_selfSlot;

protected:
    virtual void focusOutEvent(QFocusEvent *event) override;
    virtual void focusInEvent(QFocusEvent *event) override;
};

#endif // GRAPHNODESSELECTIONDIALOG_H
