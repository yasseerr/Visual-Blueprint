/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_SLOT_H
#define BP_SLOT_H

#include <QGraphicsItem>
#include <QObject>

class BP_Node;
class BP_Link;
//TODO add the link member

class BP_Slot : public QObject , public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(BP_Node* parentNode READ parentNode WRITE setParentNode NOTIFY parentNodeChanged)
    Q_PROPERTY(QList<BP_Link*> connectedLinks READ connectedLinks WRITE setConnectedLinks NOTIFY connectedLinksChanged)

    BP_Node* m_parentNode;

    QList<BP_Link*> m_connectedLinks;

    //created on mouse clicked and the added when there is a full connection
    BP_Link *temporaryLink;

public:
    explicit BP_Slot(BP_Node *parent = nullptr);

    virtual QPointF getAnchorPoint();
    virtual bool acceptConnection(BP_Slot *secondSlot);

signals:
    void parentNodeChanged(BP_Node* parentNode);

    void connectedLinksChanged(QList<BP_Link*> connectedLinks);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    BP_Node* parentNode() const;
    QList<BP_Link*> connectedLinks() const;

public slots:
    void setParentNode(BP_Node* parentNode);
    void setConnectedLinks(QList<BP_Link*> connectedLinks);

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // BP_SLOT_H
