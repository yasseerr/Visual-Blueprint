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

#include <QWidget>

namespace Ui {
class ImportsItemWidget;
}

class ImportsItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImportsItemWidget(QWidget *parent = nullptr);
    ~ImportsItemWidget();

private:
    Ui::ImportsItemWidget *ui;
};

#endif // IMPORTSITEMWIDGET_H
