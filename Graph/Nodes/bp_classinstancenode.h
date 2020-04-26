/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_CLASSINSTANCENODE_H
#define BP_CLASSINSTANCENODE_H

#include "bp_variablenode.h"

#include <QObject>

//TODO create temporary instances
class BP_ClassInstanceNode : public BP_VariableNode
{
    Q_OBJECT
public:
    BP_ClassInstanceNode();
};

#endif // BP_CLASSINSTANCENODE_H
