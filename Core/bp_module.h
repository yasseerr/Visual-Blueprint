/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_MODULE_H
#define BP_MODULE_H

#include <QObject>
class BP_Function;
class BP_Class;
class BP_Variable;

class BP_Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString alias READ alias WRITE setAlias NOTIFY aliasChanged)
    Q_PROPERTY(QList<BP_Function*> functions READ functions WRITE setFunctions NOTIFY functionsChanged)
    Q_PROPERTY(QList<BP_Class*> classes READ classes WRITE setClasses NOTIFY classesChanged)
    Q_PROPERTY(QList<BP_Variable*> moduleValues READ moduleValues WRITE setModuleValues NOTIFY moduleValuesChanged)
    Q_PROPERTY(QStringList importHierarchy READ importHierarchy WRITE setImportHierarchy NOTIFY importHierarchyChanged)

    //TODO add support for signals and slots

    QString m_name;

    QList<BP_Function*> m_functions;

    QList<BP_Class*> m_classes;

    QList<BP_Variable*> m_moduleValues;

    QString m_alias;

    QStringList m_importHierarchy;

public:

    explicit BP_Module(QVariantMap *moduleVariant = nullptr,QObject *parent = nullptr);
    QString name() const;

    QList<BP_Function*> functions() const;

    QList<BP_Class*> classes() const;

    QList<BP_Variable*> moduleValues() const;

    QString alias() const;

    QStringList importHierarchy() const;

public slots:
    void setName(QString name);

    void setFunctions(QList<BP_Function*> functions);

    void setClasses(QList<BP_Class*> classes);

    void setModuleValues(QList<BP_Variable*> moduleValues);

    void setAlias(QString alias);

    void setImportHierarchy(QStringList importHierarchy);

signals:
    void nameChanged(QString name);
    void functionsChanged(QList<BP_Function*> functions);
    void classesChanged(QList<BP_Class*> classes);
    void moduleValuesChanged(QList<BP_Variable*> moduleValues);
    void aliasChanged(QString alias);
    void importHierarchyChanged(QStringList importHierarchy);
};

#endif // BP_MODULE_H
