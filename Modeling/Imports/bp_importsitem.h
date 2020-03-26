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
    Q_PROPERTY(bool importable READ importable WRITE setImportable NOTIFY importableChanged)
    Q_PROPERTY(bool isExpanded READ isExpanded WRITE setIsExpanded NOTIFY isExpandedChanged)
    Q_PROPERTY(bool isInspectable READ isInspectable WRITE setIsInspectable NOTIFY isInspectableChanged)

    bool m_importable;
    bool m_isExpanded;
    bool m_isInspectable;

public:
    explicit BP_ImportsItem(BP_ImportsItem *parentItem,QObject *parent = nullptr);
    virtual QStringList getImportHierarchy();
    virtual QVariant getIconVariant();
    virtual void importItem();

    QString m_name = "Empty";

    ImportsModel *m_model;
    BP_ImportsItem *m_parentItem;
    QList<BP_ImportsItem*> childItems;

    bool importable() const;
    bool isExpanded() const;

    bool isInspectable() const;

public slots:
    void setImportable(bool importable);
    void setIsExpanded(bool isExpanded);
    void setIsInspectable(bool isInspectable);

signals:
    void importableChanged(bool importable);
    void isExpandedChanged(bool isExpanded);
    void isInspectableChanged(bool isInspectable);
};

#endif // BP_IMPORTSITEM_H
