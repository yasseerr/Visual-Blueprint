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

#include <QRandomGenerator>

int BP_FrameBranch::branchesCount = 0;

BP_FrameBranch::BP_FrameBranch(QObject *parent) : QObject(parent),
    m_branchID(branchesCount),
    m_branchColor(QColor::fromRgb(QRandomGenerator::global()->generate()))
{
    branchesCount++;

}

int BP_FrameBranch::branchID() const
{
    return m_branchID;
}

QList<BP_Branch *> BP_FrameBranch::previousBranches() const
{
    return m_previousBranches;
}

BP_Node *BP_FrameBranch::splitNode() const
{
    return m_splitNode;
}

void BP_FrameBranch::setBranchID(int branchID)
{
    if (m_branchID == branchID)
        return;

    m_branchID = branchID;
    emit branchIDChanged(m_branchID);
}

void BP_FrameBranch::setPreviousBranches(QList<BP_Branch *> previousBranches)
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
