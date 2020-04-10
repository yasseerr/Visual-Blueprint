/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_PARAMETER_H
#define BP_PARAMETER_H

#include <QObject>

class BP_Variable;
class BP_Class;

class BP_Parameter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString parameterName READ parameterName WRITE setParameterName NOTIFY parameterNameChanged)
    Q_PROPERTY(BP_Class* parameterClass READ parameterClass WRITE setParameterClass NOTIFY parameterClassChanged)
    Q_PROPERTY(BP_Variable* defualtValue READ defualtValue WRITE setDefualtValue NOTIFY defualtValueChanged)
    Q_PROPERTY(Kind kind READ kind WRITE setKind NOTIFY kindChanged)

    QString m_parameterName;

    BP_Class* m_parameterClass;

    BP_Variable* m_defualtValue;

public:
    enum Kind{
        POSITIONAL_OR_KEYWORD,
        KEYWORD_ONLY,
        POSITIONAL_ONLY
    };
    Q_ENUM(Kind)
    explicit BP_Parameter(QObject *parent = nullptr,QVariantMap *variableMap =nullptr);

    QString parameterName() const;

    BP_Class* parameterClass() const;

    BP_Variable* defualtValue() const;

    Kind kind() const;

public slots:
    void setParameterName(QString parameterName);

    void setParameterClass(BP_Class* parameterClass);

    void setDefualtValue(BP_Variable* defualtValue);

    void setKind(Kind kind);

signals:
    void parameterNameChanged(QString parameterName);
    void parameterClassChanged(BP_Class* parameterClass);
    void defualtValueChanged(BP_Variable* defualtValue);
    void kindChanged(Kind kind);
private:
    Kind m_kind;
};

#endif // BP_PARAMETER_H
