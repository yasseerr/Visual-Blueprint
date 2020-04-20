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

#include <QGraphicsView>
#include <QObject>

class BP_Project;
class BP_Node;

class BP_GraphView : public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(QString graphName READ graphName WRITE setGraphName NOTIFY graphNameChanged)
    Q_PROPERTY(QList<BP_Node*> nodes READ nodes WRITE setNodes NOTIFY nodesChanged)

public:
    BP_GraphView();

    void addNode(BP_Node *newNode);

    QString graphName() const;
    QList<BP_Node*> nodes() const;

public slots:
    void setGraphName(QString graphName);

    void setNodes(QList<BP_Node*> nodes);

signals:
    void graphNameChanged(QString graphName);

    void nodesChanged(QList<BP_Node*> nodes);

private:
    QGraphicsScene *m_scene;
    QString m_graphName;
    QList<BP_Node*> m_nodes;
};

#endif // BP_GRAPHVIEW_H
