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

namespace Ui {
class GraphNodesSelectionDialog;
}

class GraphNodesSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GraphNodesSelectionDialog(BP_GraphNodesModel *graphNodesModel,QWidget *parent = nullptr);
    ~GraphNodesSelectionDialog();

public slots:
    void selectionTextChanged(QString newText);

private:
    Ui::GraphNodesSelectionDialog *ui;
    BP_GraphNodesModel *m_graphNodesModel;
    QSortFilterProxyModel *m_graphProxyModel;


    // QWidget interface
protected:
    virtual void focusOutEvent(QFocusEvent *event) override;
};

#endif // GRAPHNODESSELECTIONDIALOG_H
