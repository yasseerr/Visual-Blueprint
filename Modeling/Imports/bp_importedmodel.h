/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_IMPORTEDMODEL_H
#define BP_IMPORTEDMODEL_H

#include <QAbstractItemModel>
#include <QObject>

class BP_Project;

class BP_ImportedModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(BP_Project* project READ project WRITE setProject NOTIFY projectChanged)

    BP_Project* m_project;

public:
    BP_ImportedModel();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    BP_Project* project() const;
public slots:
    void setProject(BP_Project* project);
signals:
    void projectChanged(BP_Project* project);
};

#endif // BP_IMPORTEDMODEL_H
