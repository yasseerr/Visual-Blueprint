/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_FRAMEBRANCH_H
#define BP_FRAMEBRANCH_H

#include <QColor>
#include <QObject>

class BP_Node;

class BP_FrameBranch : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int branchID READ branchID WRITE setBranchID NOTIFY branchIDChanged)
    Q_PROPERTY(QList<BP_Branch*> previousBranches READ previousBranches WRITE setPreviousBranches NOTIFY previousBranchesChanged)
    Q_PROPERTY(BP_Node* splitNode READ splitNode WRITE setSplitNode NOTIFY splitNodeChanged)
    Q_PROPERTY(QColor branchColor READ branchColor WRITE setBranchColor NOTIFY branchColorChanged)
    Q_PROPERTY(int branchLevel READ branchLevel WRITE setBranchLevel NOTIFY branchLevelChanged)
    int m_branchID;

    static int branchesCount;

    QList<BP_Branch*> m_previousBranches;

    BP_Node* m_splitNode;

    QColor m_branchColor;

    int m_branchLevel;

public:
    explicit BP_FrameBranch(QObject *parent = nullptr);

    int branchID() const;

    QList<BP_Branch*> previousBranches() const;

    BP_Node* splitNode() const;

    QColor branchColor() const
    {
        return m_branchColor;
    }

    int branchLevel() const
    {
        return m_branchLevel;
    }

public slots:
    void setBranchID(int branchID);

    void setPreviousBranches(QList<BP_Branch*> previousBranches);

    void setSplitNode(BP_Node* splitNode);

    void setBranchColor(QColor branchColor)
    {
        if (m_branchColor == branchColor)
            return;

        m_branchColor = branchColor;
        emit branchColorChanged(m_branchColor);
    }

    void setBranchLevel(int branchLevel)
    {
        if (m_branchLevel == branchLevel)
            return;

        m_branchLevel = branchLevel;
        emit branchLevelChanged(m_branchLevel);
    }

signals:

    void branchIDChanged(int branchID);
    void previousBranchesChanged(QList<BP_Branch*> previousBranches);
    void splitNodeChanged(BP_Node* splitNode);
    void branchColorChanged(QColor branchColor);
    void branchLevelChanged(int branchLevel);
};

#endif // BP_FRAMEBRANCH_H
