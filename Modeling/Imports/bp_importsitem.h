/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_IMPORTSITEM_H
#define BP_IMPORTSITEM_H

#include <QObject>

class ImportsModel;
class BP_ImportsItem : public QObject
{
    Q_OBJECT
public:
    explicit BP_ImportsItem(BP_ImportsItem *parentItem,QObject *parent = nullptr);
    virtual QStringList getImportHierarchy();
    virtual QVariant getIconVariant();

    QString m_name = "Empty";

    ImportsModel *m_model;
    BP_ImportsItem *m_parentItem;
    QList<BP_ImportsItem*> childItems;

};

#endif // BP_IMPORTSITEM_H
