/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_framebranch.h"
#include "bp_node.h"
#include "bp_graphutils.h"

#include <QRandomGenerator>

int BP_FrameBranch::branchesCount = 0;

BP_FrameBranch::BP_FrameBranch(QObject *parent) : QObject(parent),
    m_branchID(branchesCount),
    m_branchColor(QColor::fromRgb(BP_GraphUtils::colorGenerator->generate()))
{
    branchesCount++;

}

QVariant BP_FrameBranch::toVariantBP()
{
    return 0;
}

void BP_FrameBranch::fromVariant(QVariant var)
{

}

void BP_FrameBranch::getHierarchies(QList<QList<BP_Node *>*> &out)
{

    if(m_splitNode == nullptr) return;
    //get the split node
    if(m_splitNode->originalBranches().size()){
        foreach (auto branch, m_splitNode->originalBranches()) {
            QList<QList<BP_Node*>*> branchHierarchies;
            branch->getHierarchies(branchHierarchies);
            foreach (auto branchHierarchy, branchHierarchies) {
                branchHierarchy->append(m_splitNode);
                out << branchHierarchy;
            }
        }
    }
    else {
        QList<BP_Node*> retList;
        retList << m_splitNode;
        out.append(new QList<BP_Node*>(retList));
    }
    //get the split node branches and there list
}

int BP_FrameBranch::branchID() const
{
    return m_branchID;
}

QList<BP_FrameBranch *> BP_FrameBranch::previousBranches() const
{
    return m_previousBranches;
}

BP_Node *BP_FrameBranch::splitNode() const
{
    return m_splitNode;
}

QColor BP_FrameBranch::branchColor() const
{
    return m_branchColor;
}

int BP_FrameBranch::branchLevel() const
{
    return m_branchLevel;
}

QSet<BP_Thread *> BP_FrameBranch::threads() const
{
    return m_threads;
}

QSet<BP_Async *> BP_FrameBranch::asyncs() const
{
    return m_asyncs;
}

void BP_FrameBranch::setBranchID(int branchID)
{
    if (m_branchID == branchID)
        return;

    m_branchID = branchID;
    emit branchIDChanged(m_branchID);
}

void BP_FrameBranch::setPreviousBranches(QList<BP_FrameBranch *> previousBranches)
{
    if (m_previousBranches == previousBranches)
        return;

    m_previousBranches = previousBranches;
    emit previousBranchesChanged(m_previousBranches);
}

void BP_FrameBranch::setSplitNode(BP_Node *splitNode)
{
    if (m_splitNode == splitNode)
        return;

    m_splitNode = splitNode;
    emit splitNodeChanged(m_splitNode);
}

void BP_FrameBranch::setBranchColor(QColor branchColor)
{
    if (m_branchColor == branchColor)
        return;

    m_branchColor = branchColor;
    emit branchColorChanged(m_branchColor);
}

void BP_FrameBranch::setBranchLevel(int branchLevel)
{
    if (m_branchLevel == branchLevel)
        return;

    m_branchLevel = branchLevel;
    emit branchLevelChanged(m_branchLevel);
}

void BP_FrameBranch::setThreads(QSet<BP_Thread *> threads)
{
    if (m_threads == threads)
        return;

    m_threads = threads;
    emit threadsChanged(m_threads);
}

void BP_FrameBranch::setAsyncs(QSet<BP_Async *> asyncs)
{
    if (m_asyncs == asyncs)
        return;

    m_asyncs = asyncs;
    emit asyncsChanged(m_asyncs);
}
