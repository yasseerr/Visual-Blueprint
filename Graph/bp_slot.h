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

    BP_Node* m_parentNode;

public:
    explicit BP_Slot(QObject *parent = nullptr);

signals:
    void parentNodeChanged(BP_Node* parentNode);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    BP_Node* parentNode() const;
public slots:
    void setParentNode(BP_Node* parentNode);
};

#endif // BP_SLOT_H
