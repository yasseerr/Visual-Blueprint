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

#include <QtWidgets/QGraphicsItem>
#include <QObject>
#include <QTimer>

//#include "graph_interface.h"

class BP_Node;
class BP_Link;

//TODO add the link member
//Q_DECLARE_OPAQUE_POINTER(BP_Link*)
//Q_DECLARE_OPAQUE_POINTER(QList<BP_Link*>)
//Q_DECLARE_METATYPE(BP_Link*)
//typedef QList<BP_Link *> LinkList;
//Q_DECLARE_METATYPE(LinkList)

class BP_Slot : public QObject , public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(BP_Node* parentNode READ parentNode WRITE setParentNode NOTIFY parentNodeChanged)
    Q_PROPERTY(QList<BP_Link*> connectedLinks READ connectedLinks WRITE setConnectedLinks NOTIFY connectedLinksChanged)
    Q_PROPERTY(QString reference READ reference WRITE setReference NOTIFY referenceChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(bool isOutput READ isOutput WRITE setIsOutput NOTIFY isOutputChanged)
    BP_Node* m_parentNode;

    QList<BP_Link*> m_connectedLinks;

    //created on mouse clicked and the added when there is a full connection
    BP_Link *temporaryLink;

    QString m_reference;

    QColor m_textColor;

    //Timer to ignore the press event when the double click is present
    QTimer doubleClickTimer;
    QPointF scenePoseBackup;
    QPointF poseBackup;
    //QGraphicsSceneMouseEvent *mousePresedEventBackup = nullptr;

    bool m_isOutput;

public:
    explicit BP_Slot(BP_Node *parent = nullptr);

    static int slotCount;
    static int numberOfLinksCreated;
    int slotID;

    virtual QPointF getAnchorPoint();
    virtual bool acceptConnection(BP_Slot *secondSlot);
    void removeLink(BP_Link *link);
    void addLink(BP_Link *link);

    virtual QVariant toVariantBP();
    virtual void fromVariant(QVariant var);

    virtual void mouseClicked();

signals:
    void parentNodeChanged(BP_Node* parentNode);

    void connectedLinksChanged(QList<BP_Link*> connectedLinks);

    void referenceChanged(QString reference);

    void textColorChanged(QColor textColor);

    void isOutputChanged(bool isOutput);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    BP_Node* parentNode() const;
    QList<BP_Link*> connectedLinks() const;

    QString reference() const;

    QColor textColor() const;

    bool isOutput() const;

public slots:
    void setParentNode(BP_Node* parentNode);
    void setConnectedLinks(QList<BP_Link*> connectedLinks);

    // QGraphicsItem interface
    void setReference(QString reference);

    virtual void showNextNodeOptions();

    void setTextColor(QColor textColor);

    void setIsOutput(bool isOutput);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // BP_SLOT_H
