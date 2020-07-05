/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_graphutils.h"

#include <QDebug>
#include <QMetaClassInfo>
#include <QSet>

#include <Graph/Slots/bp_flowslot.h>

BP_GraphUtils* BP_GraphUtils::instance = nullptr;
int BP_GraphUtils::branchSequence = -1;

QMap<QString, QMetaObject> BP_GraphUtils::getNodeTypesMap() const
{
    return m_nodeTypesMap;
}

void BP_GraphUtils::setNodeTypesMap(const QMap<QString, QMetaObject> &nodeTypesMap)
{
    m_nodeTypesMap = nodeTypesMap;
}

QMap<QString, QList<QMetaObject> *> BP_GraphUtils::getToolNodesByCategory() const
{
    return m_toolNodesByCategory;
}

void BP_GraphUtils::setToolNodesByCategory(const QMap<QString, QList<QMetaObject> *> &toolNodesByCategory)
{
    m_toolNodesByCategory = toolNodesByCategory;
}

int BP_GraphUtils::getNewBranchID(BP_Node *parentNode)
{
    branchSequence++;
    //branchParentMap.insert(branchSequence,parents);
    auto nodeSubBr = nodeSubBranches.value(parentNode,QList<int>());
    nodeSubBr << branchSequence;
    nodeSubBranches.insert(parentNode,nodeSubBr);
    branchNodeMap.insert(branchSequence,parentNode);
//    foreach (int oneParent, parents) {
//        QList<int> parentBranches(subBranchesMap.value(oneParent));
//        parentBranches << branchSequence;
//        subBranchesMap.insert(oneParent,parentBranches);
//    }
    return branchSequence;
}

void BP_GraphUtils::setBranchSubBranches(int b, QList<int> subBranches)
{
    //branchSubBranchesCountMap.insert(b,subBranches.count());
    subBranchesMap.insert(b,QList<int>(subBranches));

}

QList<BP_Node*> BP_GraphUtils::getJoinedBranchesInList(QList<int> branches)
{
    //return the nodes that all of there sub-branches are present in the list
    // which make it a jointure

    QList<BP_Node*> retList;
    QSet<BP_Node*> branchesParentsNode;
    //get the parent of the connected branches
    foreach (int branchID, branches) {
        auto node = branchNodeMap.value(branchID);
        //cancel the root nodes with a parent branch of -1;
        if(nodeParentBranches.value(node).count()==1 && nodeParentBranches.value(node).at(0)==-1)
            continue;
        branchesParentsNode.insert(node);
    }

    //check for each parent if all the children are present
    foreach(auto brancheNode, branchesParentsNode) {

        auto subBranchesList = nodeSubBranches.value(brancheNode);
        bool joinNode = true;
        if(subBranchesList.count() == 0) joinNode = false;
        foreach (int branch, subBranchesList) {
            if(!branches.contains(branch)){
                joinNode = false;
                break;
            }
        }
        if(joinNode) retList << brancheNode;
    }
    //append the parent
    return QList<BP_Node*>(retList);
}

QList<BP_Node*> BP_GraphUtils::getJoinedBranchesInSlot(BP_FlowSlot *flowSlot)
{
    return getJoinedBranchesInList(flowSlot->branches());
}

QList<int> BP_GraphUtils::getSubBranches(int b)
{
    return subBranchesMap.value(b);
}

QList<int> BP_GraphUtils::getReplacedSubBranchesWithParents(QList<int> branches)
{
    auto parentsNode = getJoinedBranchesInList(branches);
    qDebug() << "branches to be mapped " << branches;
    qDebug() << "parent to be joined to : ";
    foreach (auto parentNode , parentsNode) {
           qDebug() << nodeSubBranches.value(parentNode);
    }

    QList<int> retList(branches);
    foreach (auto parentNode, parentsNode) {
        //replacing the childs with the parent
        foreach (int subBranch, nodeSubBranches.value(parentNode)) {
            retList.removeOne(subBranch);
        }
        retList.append(nodeParentBranches.value(parentNode));
    }
    return  retList;
}

void BP_GraphUtils::setNodeParentBranches(BP_Node *node, QList<int> branches)
{
    nodeParentBranches.insert(node,branches);
}

BP_GraphUtils::BP_GraphUtils(QObject *parent) : QObject(parent)
{

}

BP_GraphUtils *BP_GraphUtils::getInstance()
{
    if(!instance) instance = new BP_GraphUtils();
    return  instance;
}

int BP_GraphUtils::addNodeType(QMetaObject metaObj, bool isTool, QString category)
{
    m_nodeTypesMap.insert(metaObj.classInfo(metaObj.indexOfClassInfo("NodeName")).value(),metaObj);
    if(isTool){
        QList<QMetaObject>* toolsList = nullptr;
        if(m_toolNodesByCategory.contains(category)) toolsList = m_toolNodesByCategory.value(category);
        else{
            toolsList = new QList<QMetaObject>();
            m_toolNodesByCategory.insert(category,toolsList);
        }
        toolsList->append(metaObj);
    }
    return m_nodeTypesMap.size();
}
