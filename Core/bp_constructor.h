/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_CONSTRUCTOR_H
#define BP_CONSTRUCTOR_H

#include <QObject>
#include <QVariantMap>

class BP_Parameter;

class BP_Constructor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int constructorId READ constructorId WRITE setConstructorId NOTIFY constructorIdChanged)
    Q_PROPERTY(QList<BP_Parameter*> inputs READ inputs WRITE setInputs NOTIFY inputsChanged)
    Q_PROPERTY(bool hasKeyWords READ hasKeyWords WRITE setHasKeyWords NOTIFY hasKeyWordsChanged)
    Q_PROPERTY(bool hasPositional READ hasPositional WRITE setHasPositional NOTIFY hasPositionalChanged)
    int m_constructorId;

    QList<BP_Parameter*> m_inputs;

    bool m_hasKeyWords;

    bool m_hasPositional;

public:
    explicit BP_Constructor(QVariantMap *variableMap = nullptr,QObject *parent = nullptr);

    int constructorId() const;

    QList<BP_Parameter*> inputs() const;

    bool hasKeyWords() const;

    bool hasPositional() const;

public slots:
    void setConstructorId(int constructorId);

    void setInputs(QList<BP_Parameter*> inputs);

    void setHasKeyWords(bool hasKeyWords);

    void setHasPositional(bool hasPositional);

signals:

    void constructorIdChanged(int constructorId);
    void inputsChanged(QList<BP_Parameter*> inputs);
    void hasKeyWordsChanged(bool hasKeyWords);
    void hasPositionalChanged(bool hasPositional);
};

#endif // BP_CONSTRUCTOR_H
