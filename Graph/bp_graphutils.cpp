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

#include <QMetaClassInfo>

BP_GraphUtils* BP_GraphUtils::instance = nullptr;

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
