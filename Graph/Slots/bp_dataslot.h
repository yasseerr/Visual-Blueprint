/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_DATASLOT_H
#define BP_DATASLOT_H

#include <QObject>

#include <Graph/bp_slot.h>

class BP_Parameter;

class BP_DataSlot : public BP_Slot
{
    Q_OBJECT
    Q_PROPERTY(BP_Parameter* parameterObject READ parameterObject WRITE setParameterObject NOTIFY parameterObjectChanged)
    Q_PROPERTY(bool showName READ showName WRITE setShowName NOTIFY showNameChanged)
    Q_PROPERTY(QString returnName READ returnName WRITE setReturnName NOTIFY returnNameChanged)
    Q_PROPERTY(bool requireSemaphore READ requireSemaphore WRITE setRequireSemaphore NOTIFY requireSemaphoreChanged)
    BP_Parameter* m_parameterObject;
    int m_parameterWidth = 0;
    bool m_showName;

    QString m_returnName;
    
    bool m_requireSemaphore;
    
public:
    BP_DataSlot(BP_Node *parent = nullptr);

    QVariant toVariantBP() override;
    void fromVariant(QVariant var) override;

    BP_Parameter* parameterObject() const;
public slots:
    void setParameterObject(BP_Parameter* parameterObject);

    void setShowName(bool showName);

    void setReturnName(QString returnName)
    {
        if (m_returnName == returnName)
            return;

        m_returnName = returnName;
        emit returnNameChanged(m_returnName);
    }
    
    void setRequireSemaphore(bool requireSemaphore)
    {
        if (m_requireSemaphore == requireSemaphore)
            return;
        
        m_requireSemaphore = requireSemaphore;
        emit requireSemaphoreChanged(m_requireSemaphore);
    }
    
signals:
    void parameterObjectChanged(BP_Parameter* parameterObject);

    // QGraphicsItem interface

    void showNameChanged(bool showName);

    void returnNameChanged(QString returnName);
    
    void requireSemaphoreChanged(bool requireSemaphore);
    
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual QPointF getAnchorPoint() override;
    virtual bool acceptConnection(BP_Slot *secondSlot) override;
    virtual void showNextNodeOptions(QPointF dialogPos) override;
bool showName() const;
QString returnName() const
{
    return m_returnName;
}
bool requireSemaphore() const
{
    return m_requireSemaphore;
}
};

Q_DECLARE_METATYPE(BP_DataSlot*)
#endif // BP_DATASLOT_H
