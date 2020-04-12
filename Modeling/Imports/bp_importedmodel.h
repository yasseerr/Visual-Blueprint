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

#include <Core/bp_coreobject.h>

class BP_Project;

class BP_ImportedModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(BP_Project* project READ project WRITE setProject NOTIFY projectChanged)
    Q_PROPERTY(QList<BP_CoreObject*> importedList READ importedList WRITE setImportedList NOTIFY importedListChanged)
    BP_Project* m_project;

    QList<BP_CoreObject*> m_importedList;

public:
    BP_ImportedModel();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;


    BP_Project* project() const;
    QList<BP_CoreObject*> importedList() const;

public slots:
    void setProject(BP_Project* project);
    void setImportedList(QList<BP_CoreObject*> importedList);
    void addImportedObject(BP_CoreObject* importedObj);

signals:
    void projectChanged(BP_Project* project);
    void importedListChanged(QList<BP_CoreObject*> importedList);


};

#endif // BP_IMPORTEDMODEL_H
