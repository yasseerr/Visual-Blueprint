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

    //if isTool is true when the item is clicked a new Node will be created according to the TOOL_TYPE
    Q_PROPERTY(bool isTool READ isTool WRITE setIsTool NOTIFY isToolChanged)
    BP_CoreObject* m_coreObject;
    bool m_isTool;

public:

    enum TOOL_TYPE{
        NO_TOOL,INTEGER,STRING
    };
    Q_ENUM(TOOL_TYPE)
    explicit BP_GraphNodeItem(BP_GraphNodeItem *parentItem = nullptr,QObject *parent = nullptr,QString displayName="");

    ~ BP_GraphNodeItem();

    BP_Node *createToolNode(QObject *parent = nullptr);


    BP_GraphNodesModel *m_model;
    BP_GraphNodeItem *m_parentItem;
    QList<BP_GraphNodeItem*> childItems;
    QString m_displayName = "";
    TOOL_TYPE toolType = NO_TOOL;

    BP_CoreObject* coreObject() const;

    bool isTool() const;

public slots:
    void setCoreObject(BP_CoreObject* coreObject);
    void clearChildes();
    void setIsTool(bool isTool);

signals:

    void coreObjectChanged(BP_CoreObject* coreObject);
    void isToolChanged(bool isTool);
};

#endif // BP_GRAPHNODEITEM_H
