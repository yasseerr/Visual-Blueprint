/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020 by AFKAAR                                          *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *                                                                         *
 ***************************************************************************/
#include "importsmodel.h"

ImportsModel::ImportsModel()
{

}

QModelIndex ImportsModel::index(int row, int column, const QModelIndex &parent) const
{

    return  QModelIndex();
}

QModelIndex ImportsModel::parent(const QModelIndex &child) const
{

    return QModelIndex();
}

int ImportsModel::rowCount(const QModelIndex &parent) const
{

    return 0;
}

int ImportsModel::columnCount(const QModelIndex &parent) const
{

    return 0;
}

QVariant ImportsModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}
