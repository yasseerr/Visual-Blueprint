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
#include <QSet>

class BP_Node;
class BP_FrameBranch;

class BP_CoreObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QStringList importHiearchy READ importHiearchy WRITE setImportHiearchy NOTIFY importHiearchyChanged)
    Q_PROPERTY(bool isImported READ isImported WRITE setIsImported NOTIFY isImportedChanged)

    //to be used with project members
    Q_PROPERTY(bool isProjectMember READ isProjectMember WRITE setIsProjectMember NOTIFY isProjectMemberChanged)
    Q_PROPERTY(QSet<BP_FrameBranch*> connectedBranches READ connectedBranches WRITE setConnectedBranches NOTIFY connectedBranchesChanged)

    QString m_name;
    QStringList m_importHiearchy;

    bool m_isImported;

    bool m_isProjectMember;



public:

    QSet<BP_FrameBranch*> m_connectedBranches;

    explicit BP_CoreObject(QObject *parent = nullptr);

    virtual QVariant toVariantBP();

    //TODO get the importstring and type functions for the imported model
    QString getImportSourceString();
    virtual BP_Node* createNodeForObject(QObject *parent = nullptr);

    QString name() const;
    QStringList importHiearchy() const;

    bool isImported() const;

    bool isProjectMember() const;

    //? dont ever try to change the set from this function it wont work
    QSet<BP_FrameBranch*> connectedBranches();

public slots:
    void setName(QString name);
    void setImportHiearchy(QStringList importHiearchy);

    void setIsImported(bool isImported);

    void setIsProjectMember(bool isProjectMember);

    void setConnectedBranches(QSet<BP_FrameBranch*> connectedBranches);

signals:

void nameChanged(QString name);
void importHiearchyChanged(QStringList importHiearchy);
void isImportedChanged(bool isImported);
void isProjectMemberChanged(bool isProjectMember);
void connectedBranchesChanged(QSet<BP_FrameBranch*> connectedBranches);
};

#endif // BP_COREOBJECT_H
