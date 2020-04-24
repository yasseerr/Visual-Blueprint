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
    Q_PROPERTY(bool isOutput READ isOutput WRITE setIsOutput NOTIFY isOutputChanged)
    BP_Parameter* m_parameterObject;   
    bool m_isOutput;

    int m_parameterWidth = 0;
public:
    BP_DataSlot(BP_Node *parent = nullptr);
    BP_Parameter* parameterObject() const;
    bool isOutput() const;
public slots:
    void setParameterObject(BP_Parameter* parameterObject);
    void setIsOutput(bool isOutput);

signals:
    void parameterObjectChanged(BP_Parameter* parameterObject);

    // QGraphicsItem interface
    void isOutputChanged(bool isOutput);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // BP_DATASLOT_H
