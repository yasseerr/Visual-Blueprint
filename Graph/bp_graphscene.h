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

class BP_Slot;
class BP_Link;

class BP_GraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    BP_GraphScene();
    void removeLink(BP_Link *link);
    void linkRemoved(BP_Link *link);

    QStateMachine sceneState;
    //states of the sce
    QState *idleState;
    QState *removingLinkState;

    //variables for the removing link state
    BP_Link *m_removedLink = nullptr;

    // QGraphicsScene interface
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void beginRemovingLink();
    void finishRemovingLink();

};

#endif // BP_GRAPHSCENE_H
