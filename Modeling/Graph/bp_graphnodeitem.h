/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_GRAPHNODEITEM_H
#define BP_GRAPHNODEITEM_H

#include <QObject>

#include <Core/bp_coreobject.h>

class BP_GraphNodesModel;

class BP_GraphNodeItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BP_CoreObject* coreObject READ coreObject WRITE setCoreObject NOTIFY coreObjectChanged)
    BP_CoreObject* m_coreObject;

public:
    explicit BP_GraphNodeItem(BP_GraphNodeItem *parentItem = nullptr,QObject *parent = nullptr,QString displayName="");

    ~ BP_GraphNodeItem();

    BP_GraphNodesModel *m_model;
    BP_GraphNodeItem *m_parentItem;
    QList<BP_GraphNodeItem*> childItems;
    QString m_displayName = "";

    BP_CoreObject* coreObject() const;

public slots:
    void setCoreObject(BP_CoreObject* coreObject);
    void clearChildes();

signals:

    void coreObjectChanged(BP_CoreObject* coreObject);
};

#endif // BP_GRAPHNODEITEM_H
