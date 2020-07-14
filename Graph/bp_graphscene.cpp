/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_graphscene.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include <Graph/Links/bp_link.h>

BP_GraphScene::BP_GraphScene():QGraphicsScene(),
    idleState(new QState(&sceneState)),
    removingLinkState(new QState(&sceneState))
{

    sceneState.addState(idleState);
    sceneState.addState(removingLinkState);
    sceneState.setInitialState(idleState);
    idleState->addTransition(this,&BP_GraphScene::beginRemovingLink,removingLinkState);
    removingLinkState->addTransition(this,&BP_GraphScene::finishRemovingLink,idleState);
    sceneState.start();
}

void BP_GraphScene::removeLink(BP_Link *link)
{
    m_removedLink = link;
    emit beginRemovingLink();
    qDebug() << "cheking the state of the scene > " << removingLinkState->active();
    update();
}


void BP_GraphScene::linkRemoved(BP_Link *removedLink)
{
    emit finishRemovingLink();
    m_removedLink  = nullptr;
    update();
}

void BP_GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    //qDebug() << "the scene is accepting mouse events";
    if(removingLinkState->active() && m_removedLink){
        //qDebug() << "updating the output point" << (event->scenePos());
        m_removedLink->setTempOutputPoint(m_removedLink->mapFromScene(event->scenePos()));
        update();
    }

}

void BP_GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    //TODO disable the removing link state
    if(removingLinkState->active()){
        BP_Slot *selectedItem =  dynamic_cast<BP_Slot*>(itemAt(event->scenePos(),QTransform()));
        if(!selectedItem){
            m_removedLink->setVisible(false);
            removeItem(m_removedLink);
            m_removedLink->disconnectAllSlots();
            auto tmp  = m_removedLink;
            linkRemoved(m_removedLink);
            tmp->deleteLater();
        }
        else{
            //rearranging the link
            auto theOneSlotInTheLink = m_removedLink->getTheOneConnectedSlot();
            if(theOneSlotInTheLink->acceptConnection(selectedItem)){
                if(selectedItem->isOutput())
                    m_removedLink->setInSlot(selectedItem);
                else
                    m_removedLink->setOutSlot(selectedItem);
                //m_removedLink->setOutSlot(selectedItem);
                theOneSlotInTheLink->addLink(m_removedLink);
                selectedItem->addLink(m_removedLink);
                linkRemoved(m_removedLink);
            }
        }

    }else{
        QGraphicsScene::mousePressEvent(event);
    }
}
