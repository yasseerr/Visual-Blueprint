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
#include "bp_slot.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include <Graph/Links/bp_link.h>

#include <Core/bp_coreobject.h>

#define DOUBLE_CLICK_INTERVAL 200

int BP_Slot::slotCount = 0;
int BP_Slot::numberOfLinksCreated = 0;

BP_Slot::BP_Slot(BP_Node *parent) : QObject(parent),m_parentNode(parent),m_reference("unknown"),m_textColor(Qt::white)
{
    slotID = slotCount;
    BP_GraphUtils::getInstance()->registerSlotID(slotID,this);
    slotCount++;
    setParentItem(parent);
    doubleClickTimer.setInterval(DOUBLE_CLICK_INTERVAL);
    doubleClickTimer.setSingleShot(true);
    connect(&doubleClickTimer,&QTimer::timeout,this,&BP_Slot::mouseClicked);
}

QPointF BP_Slot::getAnchorPoint()
{
    return scenePos() + QPoint(7,7);
}

bool BP_Slot::acceptConnection(BP_Slot *secondSlot)
{
    if(secondSlot->parentNode() == this->parentNode())
        return false;
    return true;
}

void BP_Slot::removeLink(BP_Link *link)
{
    m_connectedLinks.removeOne(link);
}

void BP_Slot::addLink(BP_Link *link)
{
    m_connectedLinks << link;
}

QVariant BP_Slot::toVariantBP()
{
    //TODO when loading links verify if the connection already exist in the other direction
    QVariantMap retMap ;
    retMap["slotID"] = slotID;
    retMap["type"] = "default" ;
    retMap["reference"] = m_reference;
    retMap["isOutput"] = m_isOutput;

    QVariantList linksVariant;
    foreach (auto linkVariant, m_connectedLinks) {
        linksVariant << linkVariant->toVariantBP();
    }
    retMap["connectedLinks"] = linksVariant;
    return retMap;

}

void BP_Slot::fromVariant(QVariant var)
{
    auto varMap = var.toMap();
    slotID = varMap["slotID"].toInt();
    BP_GraphUtils::getInstance()->registerSlotID(slotID,this);
    //setReference(varMap["reference"].toString());
    //setIsOutput(varMap["isOutput"].toBool());
    auto connectedLinksVariant = varMap["connectedLinks"].toList();
    foreach (auto linkVar, connectedLinksVariant) {
        //creating the link
        auto linkVarMap = linkVar.toMap();
        auto inSlot = BP_GraphUtils::getInstance()->getSlotByID(linkVarMap["inSlot"].toInt());
        auto outSlot = BP_GraphUtils::getInstance()->getSlotByID(linkVarMap["outSlot"].toInt());
        if(!inSlot || !outSlot){
            qDebug() << "one skipped connection";
            continue;
        }
        BP_Link *newLink = new BP_Link(this);
        //this->scene()->addItem(newLink);
        BP_Slot::numberOfLinksCreated ++;
        qDebug() << "number of links created" << BP_Slot::numberOfLinksCreated;
        inSlot->addLink(newLink);
        outSlot->addLink(newLink);
        newLink->setInSlot(inSlot);
        newLink->setOutSlot(outSlot);
        inSlot->acceptConnection(outSlot);
        auto graphScene = qobject_cast<BP_GraphScene*>(scene());
        parentNode()->connectedGraph()->scene()->addItem(newLink);

    }

}

void BP_Slot::mouseClicked()
{
    qDebug() << "pressed at position" << poseBackup;
    temporaryLink = new BP_Link();
    if(this->isOutput())
        temporaryLink->setInSlot(this);
    else
        temporaryLink->setOutSlot(this);
    this->scene()->addItem(temporaryLink);
    temporaryLink->setTempOutputPoint(scenePoseBackup);
}

QList<BP_FrameBranch *> BP_Slot::getJoinedBranches()
{
    QList<BP_FrameBranch*> branchesToBeFiltered(m_frameBranches);

    //get the parents
    QSet<BP_Node*> splitNodes;
    foreach (auto frameBranch, m_frameBranches) {
        if(frameBranch->splitNode()->subBranches().size()<2)continue;
        splitNodes << frameBranch->splitNode();
    }
    //see if all the parents subbranches are present
    QList<BP_FrameBranch*> newBranchesList;
    foreach (auto splitNode, splitNodes) {
        bool splitNodeJoined = true;
        foreach (auto splitNodeSubBranch, splitNode->subBranches()) {
            if(!frameBranches().contains(splitNodeSubBranch)){
                splitNodeJoined = false;
                break;
            }
        }
        //test if the split node was joined
        if(splitNodeJoined){
            qDebug() << "branch was joined from node " << splitNode->nodeId;
            foreach (auto branch, splitNode->subBranches()) {
                branchesToBeFiltered.removeOne(branch);
            }
            branchesToBeFiltered << splitNode->originalBranches();
            splitNode->setClotureNode(this->parentNode());
        }
    }

    //replace the subBranches by the original branch
    // create the subBranchesList for node
    // create the originalBranches for node
    return QList<BP_FrameBranch*>(branchesToBeFiltered);
}

QSet<BP_Thread *> BP_Slot::getJoinedThreads()
{
    QSet<BP_Thread*> retSet;
    auto branches = getJoinedBranches();
    foreach (auto branch, branches) {
        retSet.unite(branch->threads());
    }
    return QSet<BP_Thread*>(retSet);
}

void BP_Slot::notifyConnectedNodes()
{
    foreach (auto link, m_connectedLinks) {
        if(this->isOutput()){
            link->outSlot()->parentNode()->updateSlotsBranches(link->outSlot());
        }
        else{
            link->inSlot()->parentNode()->updateSlotsBranches(link->inSlot());
        }
    }
}


QRectF BP_Slot::boundingRect() const
{
    return QRectF(0,0,15,15);
}

void BP_Slot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(boundingRect());

}

BP_Node *BP_Slot::parentNode() const
{
    return m_parentNode;
}

QList<BP_Link *> BP_Slot::connectedLinks() const
{
    return m_connectedLinks;
}

QString BP_Slot::reference() const
{
    return m_reference;
}

QColor BP_Slot::textColor() const
{
    return m_textColor;
}

bool BP_Slot::isOutput() const
{
    return m_isOutput;
}

QList<BP_FrameBranch *> BP_Slot::frameBranches() const
{
    return m_frameBranches;
}

void BP_Slot::setParentNode(BP_Node *parentNode)
{
    if (m_parentNode == parentNode)
        return;

    m_parentNode = parentNode;
    emit parentNodeChanged(m_parentNode);
}

void BP_Slot::setConnectedLinks(QList<BP_Link *> connectedLinks)
{
    if (m_connectedLinks == connectedLinks)
        return;

    m_connectedLinks = connectedLinks;
    emit connectedLinksChanged(m_connectedLinks);
}

void BP_Slot::setReference(QString reference)
{
    if (m_reference == reference)
        return;

    m_reference = reference;
    emit referenceChanged(m_reference);
}

void BP_Slot::showNextNodeOptions()
{


}

void BP_Slot::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(m_textColor);
}

void BP_Slot::setIsOutput(bool isOutput)
{
    if (m_isOutput == isOutput)
        return;

    m_isOutput = isOutput;
    emit isOutputChanged(m_isOutput);
}

void BP_Slot::setFrameBranches(QList<BP_FrameBranch *> frameBranches)
{
    if (m_frameBranches == frameBranches)
        return;

    m_frameBranches = frameBranches;
    emit frameBranchesChanged(m_frameBranches);
}

void BP_Slot::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsItem::mousePressEvent(event);
    scenePoseBackup = event->scenePos();
    poseBackup = event->pos();
    doubleClickTimer.start(DOUBLE_CLICK_INTERVAL);
}

void BP_Slot::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //stop the event when the signal is not defined yet
    if(doubleClickTimer.isActive()) return;
    //analysing the state of the scene
    auto graphScene = qobject_cast<BP_GraphScene*>(scene());
    if(graphScene->removingLinkState->active()) return;

    //qDebug() << "mouse moved " << event->pos();
    temporaryLink->setTempOutputPoint(temporaryLink->mapFromScene(mapToScene(event->pos())));
    //TODO update only the rect arround the link
    scene()->update();
    //temporaryLink->update();
}

void BP_Slot::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //analysing the state of the scene
    auto graphScene = qobject_cast<BP_GraphScene*>(scene());
    if(graphScene->removingLinkState->active()) return;
    if(doubleClickTimer.isActive()) return;

    qDebug() << "mouse released " << event->pos();
    BP_Slot *selectedItem =  dynamic_cast<BP_Slot*>(scene()->itemAt(event->scenePos(),QTransform()));
    if(selectedItem != nullptr){
        //qDebug() << " selected item " << selectedItem->parentNode()->coreObject()->name();
        //TODO filter the allowed connection
        if(acceptConnection(selectedItem)){
            if(selectedItem->isOutput())
                temporaryLink->setInSlot(selectedItem);
            else
                temporaryLink->setOutSlot(selectedItem);
            m_connectedLinks << temporaryLink;
            selectedItem->addLink(temporaryLink);
        }
        else{
            temporaryLink->setVisible(false);
            scene()->removeItem(temporaryLink);
            temporaryLink->deleteLater();
        }

    }
    else{
        showNextNodeOptions();
        temporaryLink->setVisible(false);
        scene()->removeItem(temporaryLink);
        temporaryLink->deleteLater();
    }
    scene()->update();
}

void BP_Slot::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "entering the double click function";
    doubleClickTimer.stop();
    //QGraphicsItem::mouseDoubleClickEvent(event);
    qDebug() << "the slout is double clicked";
    if(connectedLinks().size()==0) return;
    //disconnect the link
    auto link = connectedLinks().last();
    link->disconnectSlot(this);
    m_connectedLinks.removeOne(link);

    //notify the scene
    auto graph_scene = qobject_cast<BP_GraphScene*>(scene());
    if(!graph_scene) return;
    //rename to unplug instead
    graph_scene->removeLink(link);

    //cancel or validate when clicked
}
