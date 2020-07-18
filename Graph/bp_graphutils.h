/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_GRAPHUTILS_H
#define BP_GRAPHUTILS_H

#define RegisterNodeType(X) int X::nodeTypeID= BP_GraphUtils::getInstance()->addNodeType(X::staticMetaObject);
#define RegisterToolNodeType(X,Category) int X::nodeTypeID = BP_GraphUtils::getInstance()->addNodeType(X::staticMetaObject,true,Category);

#include <QColor>
#include <QMap>
#include <QObject>

class BP_FlowSlot;
class BP_Node;
class BP_Slot;

class BP_GraphUtils : public QObject
{
    Q_OBJECT

    static BP_GraphUtils* instance ;
    QMap<QString,QMetaObject> m_nodeTypesMap;
    QMap<QString,QList<QMetaObject>*> m_toolNodesByCategory;

    //branches variables
    static int branchSequence;
    //QMap<int,int> branchSubBranchesCountMap;
    QMap<int,QList<int>> branchParentMap;
    QMap<int,QList<int>> subBranchesMap;
    QMap<int,QColor> branchesColors;
    QMap<int,BP_Node*> parentNodeMap;

    QMap<BP_Node*,QList<int>> nodeSubBranches;
    QMap<BP_Node*,QList<int>> nodeParentBranches;
    QMap<int,BP_Node *> branchNodeMap;
    QMap<BP_Node*,BP_Node*> endOfBlockRegister;

    //indecies
    QMap<int,BP_Node*> nodesIndex;
    QMap<int,BP_Slot*> slotsIndex;

public:
    explicit BP_GraphUtils(QObject *parent = nullptr);
    static BP_GraphUtils* getInstance();
    int addNodeType(QMetaObject metaObj,bool isTool = false,QString category= "");

    QMap<QString, QMetaObject> getNodeTypesMap() const;
    void setNodeTypesMap(const QMap<QString, QMetaObject> &nodeTypesMap);

    QMap<QString, QList<QMetaObject> *> getToolNodesByCategory() const;
    void setToolNodesByCategory(const QMap<QString, QList<QMetaObject> *> &toolNodesByCategory);

    BP_Node *createNode(QString type);

    void registerNodeID(int id,BP_Node*  node);
    void registerSlotID(int id,BP_Slot* slot);

    BP_Node* getNodeByID(int id);
    BP_Slot* getSlotByID(int id);

    //branches functions
    int getNewBranchID(BP_Node *parentNode);
    void setBranchSubBranches(int b,QList<int> subBranches);
    QList<BP_Node*> getJoinedBranchesInList(QList<int> branches);
    QList<BP_Node*> getJoinedBranchesInSlot(BP_FlowSlot *flowSlot);
    QList<int> getSubBranches(int b);
    QList<int> getReplacedSubBranchesWithParents(BP_FlowSlot *flowSlot);
    void setNodeParentBranches(BP_Node* node,QList<int> branches);
    BP_Node* getEndOfBranchForNode(BP_Node* node);


signals:

};

#endif // BP_GRAPHUTILS_H
