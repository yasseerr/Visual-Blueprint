/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "renderimportfilter.h"

#include <QDebug>
#include <grantlee/util.h>

QVariant RenderImportFilter::doFilter(const QVariant &input, const QVariant &argument, bool autoescape) const
{
    qDebug() << Grantlee::getSafeString(argument).get();
    if(input.canConvert<QVariantList>()){
       if(Grantlee::getSafeString(argument) == "class" ||
               Grantlee::getSafeString(argument) == "function" ||
               Grantlee::getSafeString(argument) == "variable"){
            QStringList importHierarchy = input.toStringList();
            QString className = importHierarchy.first();
            importHierarchy.takeFirst();
            std::reverse(importHierarchy.begin(),importHierarchy.end());
            QString modulepath = importHierarchy.join(".");
            return "from "+modulepath+" import "+className;
       }
       else if (Grantlee::getSafeString(argument) == "module") {
           QStringList importHierarchy = input.toStringList();
           std::reverse(importHierarchy.begin(),importHierarchy.end());
           QString modulepath = importHierarchy.join(".");
           return "from "+modulepath+" import *";
       }
        return input.toList().count()+10;
    }
    return  "failed";

}

bool RenderImportFilter::isSafe() const
{
    return true;
}

QVariant RenderParametersFilter::doFilter(const QVariant &input, const QVariant &argument, bool autoescape) const
{
    auto parameterList = input.toList();
    foreach (QVariant parameter, parameterList) {
        qDebug()<< "parameterName"   << parameter.toHash().value("parameterName").toString();
    }
    return "parameter";
}

bool RenderParametersFilter::isSafe() const
{
    return true;
}
