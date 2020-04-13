/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef VARIABLEEDITORWIDGET_H
#define VARIABLEEDITORWIDGET_H

#include <QStandardItemModel>
#include <QStringListModel>
#include <QWidget>

#include <Core/bp_project.h>

namespace Ui {
class VariableEditorWidget;
}

class VariableEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VariableEditorWidget(QWidget *parent = nullptr);
    ~VariableEditorWidget();

    void setEditorData(QString className,int multiplicityIndex);
    void setComboModel(QStringList classesList);

    QString getClassName();
    int getMultiplictyIndex();

    BP_Project *m_project;
    QStandardItemModel *multiplicityModel;
    QStringListModel *classesModel;

public slots:
    void onConfirmClicked();
signals:
    void changeCommited(QWidget *editor);

private:
    Ui::VariableEditorWidget *ui;
};

#endif // VARIABLEEDITORWIDGET_H
