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
#include <QSet>
#include <QVariant>

class BP_Node;
class BP_Thread;
class BP_Async;

class BP_FrameBranch : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int branchID READ branchID WRITE setBranchID NOTIFY branchIDChanged)
    Q_PROPERTY(QList<BP_FrameBranch*> previousBranches READ previousBranches WRITE setPreviousBranches NOTIFY previousBranchesChanged)
    Q_PROPERTY(BP_Node* splitNode READ splitNode WRITE setSplitNode NOTIFY splitNodeChanged)
    Q_PROPERTY(QColor branchColor READ branchColor WRITE setBranchColor NOTIFY branchColorChanged)
    Q_PROPERTY(int branchLevel READ branchLevel WRITE setBranchLevel NOTIFY branchLevelChanged)
    Q_PROPERTY(QSet<BP_Thread*> threads READ threads WRITE setThreads NOTIFY threadsChanged)
    Q_PROPERTY(QSet<BP_Async*> asyncs READ asyncs WRITE setAsyncs NOTIFY asyncsChanged)

    int m_branchID;

    static int branchesCount;


    BP_Node* m_splitNode;

    QColor m_branchColor;

    int m_branchLevel;


public:
    QSet<BP_Thread*> m_threads;
    QList<BP_FrameBranch*> m_previousBranches;
    QSet<BP_Async*> m_asyncs;

public:
    explicit BP_FrameBranch(QObject *parent = nullptr);

    virtual QVariant toVariantBP();
    virtual void fromVariant(QVariant var);

    void getHierarchies(QList<QList<BP_Node*>*> &out);

    int branchID() const;

    QList<BP_FrameBranch*> previousBranches() const;

    BP_Node* splitNode() const;

    QColor branchColor() const;

    int branchLevel() const;

    QSet<BP_Thread*> threads() const;

    QSet<BP_Async*> asyncs() const;

public slots:
    void setBranchID(int branchID);

    void setPreviousBranches(QList<BP_FrameBranch*> previousBranches);

    void setSplitNode(BP_Node* splitNode);

    void setBranchColor(QColor branchColor);

    void setBranchLevel(int branchLevel);

    void setThreads(QSet<BP_Thread*> threads);

    void setAsyncs(QSet<BP_Async*> asyncs);

signals:

    void branchIDChanged(int branchID);
    void previousBranchesChanged(QList<BP_FrameBranch*> previousBranches);
    void splitNodeChanged(BP_Node* splitNode);
    void branchColorChanged(QColor branchColor);
    void branchLevelChanged(int branchLevel);
    void threadsChanged(QSet<BP_Thread*> threads);
    void asyncsChanged(QSet<BP_Async*> asyncs);
};

#endif // BP_FRAMEBRANCH_H
