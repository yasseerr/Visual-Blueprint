/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef IMPORTSITEMWIDGET_H
#define IMPORTSITEMWIDGET_H

#include <QAbstractItemModel>
#include <QWidget>

#include <Modeling/Imports/bp_importsitem.h>

namespace Ui {
class ImportsItemWidget;
}

class ImportsItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImportsItemWidget(BP_ImportsItem *importItem,const QModelIndex widgetModelIndex,QWidget *parent = nullptr);
    ~ImportsItemWidget();

    QModelIndex m_widgetModelIndex;
    BP_ImportsItem *m_importsItem;

public slots:
    void onInspectClicked();

private:
    Ui::ImportsItemWidget *ui;
};

#endif // IMPORTSITEMWIDGET_H
