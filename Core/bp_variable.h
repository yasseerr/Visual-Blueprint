/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_VARIABLE_H
#define BP_VARIABLE_H

#include <QObject>

class BP_Variable : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString variableName READ variableName WRITE setVariableName NOTIFY variableNameChanged)
    Q_PROPERTY(bool isPrimitive READ isPrimitive WRITE setIsPrimitive NOTIFY isPrimitiveChanged)
    QString m_variableName;

    bool m_isPrimitive;

public:
    explicit BP_Variable(QObject *parent = nullptr);

    QString variableName() const;

    bool isPrimitive() const;

public slots:
    void setVariableName(QString variableName);

    void setIsPrimitive(bool isPrimitive);

signals:
    void variableNameChanged(QString variableName);
    void isPrimitiveChanged(bool isPrimitive);
};

#endif // BP_VARIABLE_H
