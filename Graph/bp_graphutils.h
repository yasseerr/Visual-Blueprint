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

class BP_GraphUtils : public QObject
{
    Q_OBJECT

    static BP_GraphUtils* instance ;
    QMap<QString,QMetaObject> m_nodeTypesMap;
    QMap<QString,QList<QMetaObject>*> m_toolNodesByCategory;

    //branches variables
    static int branchSequence;
    QMap<int,int> branchSubBranchesCountMap;
    QMap<int,int> branchParentMap;
    QMap<int,QList<int>> subBranchesMap;
    QMap<int,QColor> branchesColors;

public:
    explicit BP_GraphUtils(QObject *parent = nullptr);
    static BP_GraphUtils* getInstance();
    int addNodeType(QMetaObject metaObj,bool isTool = false,QString category= "");

    QMap<QString, QMetaObject> getNodeTypesMap() const;
    void setNodeTypesMap(const QMap<QString, QMetaObject> &nodeTypesMap);

    QMap<QString, QList<QMetaObject> *> getToolNodesByCategory() const;
    void setToolNodesByCategory(const QMap<QString, QList<QMetaObject> *> &toolNodesByCategory);

    //branches functions
    int getNewBranchID();
    void setBranchSubBranches(int b,QList<int> subBranches);
    QList<int> getJoinedBranchesInSlot(BP_FlowSlot *flowSlot);
    QList<int> getSubBranches(int b);


signals:

};

#endif // BP_GRAPHUTILS_H
