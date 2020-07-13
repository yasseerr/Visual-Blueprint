/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_GRAPHVIEW_H
#define BP_GRAPHVIEW_H

#include "bp_graphscene.h"

#include <QGraphicsView>
#include <QObject>

class BP_Project;
class BP_Node;
class BP_EventNode;

class BP_GraphView : public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(QString graphName READ graphName WRITE setGraphName NOTIFY graphNameChanged)
    Q_PROPERTY(QList<BP_Node*> nodes READ nodes WRITE setNodes NOTIFY nodesChanged)
    Q_PROPERTY(BP_EventNode* entryNode READ entryNode WRITE setEntryNode NOTIFY entryNodeChanged)

public:
    BP_GraphView();

    void addNode(BP_Node *newNode,QPoint globalPosition);

    QString graphName() const;
    QList<BP_Node*> nodes() const;

    BP_EventNode* entryNode() const;

public slots:
    void setGraphName(QString graphName);

    void setNodes(QList<BP_Node*> nodes);

    void setEntryNode(BP_EventNode* entryNode);

signals:
    void graphNameChanged(QString graphName);

    void nodesChanged(QList<BP_Node*> nodes);

    void entryNodeChanged(BP_EventNode* entryNode);

private:
    BP_GraphScene *m_scene;
    QString m_graphName;
    QList<BP_Node*> m_nodes;
    BP_EventNode* m_entryNode;
};

#endif // BP_GRAPHVIEW_H
