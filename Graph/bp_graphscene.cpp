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

BP_GraphScene::BP_GraphScene():QGraphicsScene()
{
    sceneState.setInitialState(&idleState);
    idleState.addTransition(this,&BP_GraphScene::beginRemovingLink,&removingLinkState);
    removingLinkState.addTransition(this,&BP_GraphScene::finishRemovingLink,&idleState);
    sceneState.start();
}

void BP_GraphScene::linkRemoved(BP_Slot *endSlot)
{

}

void BP_GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    qDebug() << "the scene is accepting mouse events";
    if(removingLinkState.active());

}
