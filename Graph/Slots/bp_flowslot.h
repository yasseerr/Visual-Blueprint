/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_FLOWSLOT_H
#define BP_FLOWSLOT_H

#include <QObject>

#include <Graph/bp_slot.h>

class BP_FlowSlot : public BP_Slot
{
    Q_OBJECT
    Q_PROPERTY(QString flowName READ flowName WRITE setFlowName NOTIFY flowNameChanged)
    Q_PROPERTY(bool showFlowName READ showFlowName WRITE setShowFlowName NOTIFY showFlowNameChanged)
    Q_PROPERTY(QList<int> branches READ branches WRITE setBranches NOTIFY branchesChanged)
    Q_PROPERTY(QList<BP_FrameBranch*> frameBranches READ frameBranches WRITE setFrameBranches NOTIFY frameBranchesChanged)

    QPolygon trianglePolygone;

    QString m_flowName;

    bool m_showFlowName;

    int flowNameWidth = 0;

    //the branches going into the slot
    QList<int> m_branches;

    QList<BP_FrameBranch*> m_frameBranches;

public:
    BP_FlowSlot(BP_Node *parent = nullptr);
    QVariant toVariantBP() override;
    void fromVariant(QVariant var) override;

    virtual bool acceptConnection(BP_Slot *secondSlot) override;
    void addBranch(int branch);

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override;
    virtual QPointF getAnchorPoint() override;
    QString flowName() const;
    bool showFlowName() const;

    QList<int> branches() const;

    QList<BP_FrameBranch*> frameBranches() const
    {
        return m_frameBranches;
    }

public slots:
    void setFlowName(QString flowName);
    void setShowFlowName(bool showFlowName);

    void setBranches(QList<int> branches);

    void setFrameBranches(QList<BP_FrameBranch*> frameBranches)
    {
        if (m_frameBranches == frameBranches)
            return;

        m_frameBranches = frameBranches;
        emit frameBranchesChanged(m_frameBranches);
    }

signals:
    void flowNameChanged(QString flowName);
    void showFlowNameChanged(bool showFlowName);


    void branchesChanged(QList<int> branches);
    void frameBranchesChanged(QList<BP_FrameBranch*> frameBranches);
};

#endif // BP_FLOWSLOT_H
