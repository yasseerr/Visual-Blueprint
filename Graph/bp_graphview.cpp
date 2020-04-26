/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_graphview.h"
#include "bp_node.h"

BP_GraphView::BP_GraphView():QGraphicsView(),m_graphName("New Graph"),m_scene(new QGraphicsScene())
{
    //configure the view
    this->setMouseTracking(true);

    this->setScene(m_scene);
    setRenderHint(QPainter::Antialiasing);
}

void BP_GraphView::addNode(BP_Node *newNode,QPoint globalPosition)
{
    auto newNodePos = mapFromGlobal(globalPosition);
    newNode->setPos( mapToScene(newNodePos));
    m_nodes.append(newNode);
    m_scene->addItem(newNode);
    m_scene->update(newNode->boundingRect());
}

QString BP_GraphView::graphName() const
{
    return m_graphName;
}

QList<BP_Node *> BP_GraphView::nodes() const
{
    return m_nodes;
}

void BP_GraphView::setGraphName(QString graphName)
{
    if (m_graphName == graphName)
        return;

    m_graphName = graphName;
    emit graphNameChanged(m_graphName);
}

void BP_GraphView::setNodes(QList<BP_Node *> nodes)
{
    if (m_nodes == nodes)
        return;

    m_nodes = nodes;
    emit nodesChanged(m_nodes);
}
