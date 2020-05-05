/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef RENDERIMPORTFILTER_H
#define RENDERIMPORTFILTER_H

#include <grantlee/filter.h>

class RenderImportFilter :public Grantlee::Filter
{

public:
    virtual QVariant doFilter(const QVariant &input, const QVariant &argument, bool autoescape) const override;
    bool isSafe() const override;
};

class RenderParametersFilter :public Grantlee::Filter
{

public:
    virtual QVariant doFilter(const QVariant &input, const QVariant &argument, bool autoescape) const override;
    bool isSafe() const override;
};

#endif // RENDERIMPORTFILTER_H
