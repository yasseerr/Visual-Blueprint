/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef IMPORTEDDELEGATEWIDGET_H
#define IMPORTEDDELEGATEWIDGET_H

#include <QWidget>

namespace Ui {
class ImportedDelegateWidget;
}

class ImportedDelegateWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString importedName READ importedName WRITE setImportedName NOTIFY importedNameChanged)
    Q_PROPERTY(QString importedSourceModule READ importedSourceModule WRITE setImportedSourceModule NOTIFY importedSourceModuleChanged)

public:
    explicit ImportedDelegateWidget(QWidget *parent = nullptr);
    ~ImportedDelegateWidget();

    QString importedName() const;

    QString importedSourceModule() const;

public slots:
    void setImportedName(QString importedName);

    void setImportedSourceModule(QString importedSourceModule);

    void onRemoveImportClicked();

signals:
    void importedNameChanged(QString importedName);

    void importedSourceModuleChanged(QString importedSourceModule);

private:
    Ui::ImportedDelegateWidget *ui;
    QString m_importedName;
    QString m_importedSourceModule;
};

#endif // IMPORTEDDELEGATEWIDGET_H
