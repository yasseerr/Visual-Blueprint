/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_LOGICALNODE_H
#define BP_LOGICALNODE_H

#include <Graph/bp_node.h>



class BP_LogicalNode : public BP_Node
{
    Q_OBJECT
public:
    Q_CLASSINFO("name","Logical")
    BP_LogicalNode();
};

#endif // BP_LOGICALNODE_H
