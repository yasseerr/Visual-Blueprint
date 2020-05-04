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


QVariant RenderImportFilter::doFilter(const QVariant &input, const QVariant &argument, bool autoescape) const
{
    if(input.canConvert<QVariantList>()){
        //if(input.toString() == "module")
       return input.toList().count()+10;
    }
    return  "failed";

}

bool RenderImportFilter::isSafe() const
{
    return true;
}
