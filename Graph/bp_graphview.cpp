/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_framebranch.h"
#include "bp_graphutils.h"
#include "bp_graphview.h"
#include "bp_node.h"
#include "bp_thread.h"
#include <QDragEnterEvent>

#include <Graph/Nodes/bp_eventnode.h>

#include <Graph/Slots/bp_flowslot.h>

#include <QMimeData>
#include <bp_utils.h>
#include <qdebug.h>

BP_GraphView::BP_GraphView():QGraphicsView(),m_graphName("New Graph"),m_scene(new BP_GraphScene()),m_entryNode(new BP_EventNode())
{
    //configure the view
    this->setMouseTracking(true);
    this->setAcceptDrops(true);

    this->setScene(m_scene);
    setRenderHint(QPainter::Antialiasing);


    //configuring the event
    m_entryNode->setEventName("Entry");
    auto enteredEvent = m_entryNode->createFlow("entered");
    BP_Thread *mainThread  = new BP_Thread(enteredEvent);
    enteredEvent->m_frameBranches.first()->m_threads << mainThread;

    //BP_GraphUtils::getInstance()->setNodeParentBranches(m_entryNode,QList<int>() << -1);
    //branch 0 the start
    //enteredEvent->addBranch(BP_GraphUtils::getInstance()->getNewBranchID(m_entryNode));

    m_entryNode->createFlow("exited");
    m_entryNode->createFlow("flow");
    scene()->addItem(m_entryNode);
    m_entryNode->setPos(0,0);
}

QVariant BP_GraphView::toVariantBP()
{
    QVariantMap retMap;
    retMap["entryNode"] = m_entryNode->toVariantBP();
    //save the Nodes
    QVariantList nodesVariantList;
    foreach (auto node, m_nodes) {
        if(node==m_entryNode) continue;
        nodesVariantList << node->toVariantBP();
    }
    retMap["nodes"] = nodesVariantList;
    return retMap;
}

void BP_GraphView::fromVariantBP(QVariant var)
{
    QVariantMap graphMap = var.toMap();
    foreach (auto var, graphMap["nodes"].toList()) {
        auto nodeMap =var.toMap();
        BP_Node *node = BP_GraphUtils::getInstance()->createNode(nodeMap["type"].toString());
        this->addNode(node,QPoint(0,0));
        node->fromVariant(nodeMap);
    }
    entryNode()->fromVariant(graphMap["entryNode"]);

}

void BP_GraphView::addNode(BP_Node *newNode,QPoint globalPosition)
{
    newNode->setConnectedGraph(this);
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

BP_EventNode *BP_GraphView::entryNode() const
{
    return m_entryNode;
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

void BP_GraphView::setEntryNode(BP_EventNode *entryNode)
{
    if (m_entryNode == entryNode)
        return;

    m_entryNode = entryNode;
    emit entryNodeChanged(m_entryNode);
}

void BP_GraphView::dragEnterEvent(QDragEnterEvent *event){
    QGraphicsView::dragEnterEvent(event);
    event->acceptProposedAction();
}
void BP_GraphView::dropEvent(QDropEvent *event){
    if(event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")){
        qDebug() << "the drop event has the model format";
        QByteArray encoded = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
        QDataStream stream(&encoded, QIODevice::ReadOnly);
        //reading the mime data from the membersitem
        while (!stream.atEnd())
        {
            int row, col;
            QMap<int,  QVariant> roleDataMap;
            stream >> row >> col >> roleDataMap;
            if(row == 0 && col == 0){
                //get the variable with the name in the first role
                auto memberVariableName  = roleDataMap[0].toString();
                qDebug() << "membrr variablee detected : " << memberVariableName;
                auto memberObject = BP_Utils::instance()->coreObjectsMap.value(memberVariableName);
                //if(!memberObject)return;
                auto memberNode = memberObject->createNodeForObject(nullptr,this);
                this->addNode(memberNode,this->mapToGlobal(event->pos()));
                //create the node as  is the graph selection dialog
            }

        }
    }
    QGraphicsView::dropEvent(event);
    event->acceptProposedAction();
}

void BP_GraphView::dragMoveEvent(QDragMoveEvent *event)
{
    QGraphicsView::dragMoveEvent(event);
    event->acceptProposedAction();
}
