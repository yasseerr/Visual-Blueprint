/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_ADDNODE_H
#define BP_ADDNODE_H

#include <QObject>

#include <Graph/bp_node.h>

class BP_AddNode : public BP_Node
{
    Q_OBJECT
    Q_CLASSINFO("name","Add")
public:
    BP_AddNode();
};

#endif // BP_ADDNODE_H
