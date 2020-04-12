/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_COREOBJECT_H
#define BP_COREOBJECT_H

#include <QObject>

class BP_CoreObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QStringList importHiearchy READ importHiearchy WRITE setImportHiearchy NOTIFY importHiearchyChanged)

    QString m_name;
    QStringList m_importHiearchy;

public:

    explicit BP_CoreObject(QObject *parent = nullptr);

    //TODO get the importstring and type functions for the imported model
    QString getImportSourceString();

    QString name() const;
    QStringList importHiearchy() const;

public slots:
    void setName(QString name);
    void setImportHiearchy(QStringList importHiearchy);

signals:

void nameChanged(QString name);
void importHiearchyChanged(QStringList importHiearchy);
};

#endif // BP_COREOBJECT_H
