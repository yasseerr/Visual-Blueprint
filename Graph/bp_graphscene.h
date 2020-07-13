/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_GRAPHSCENE_H
#define BP_GRAPHSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QStateMachine>

class BP_GraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    BP_GraphScene();

    QStateMachine sceneState;
    //states of the sce
    QState idleState;
    QState removingLinkState;

    // QGraphicsScene interface
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

public signals:
    void beginRemovingLink();
    void finishRemovingLink();

};

#endif // BP_GRAPHSCENE_H
