/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_flowslot.h"

#include <QDebug>
#include <QVariantList>
#include <QVariantMap>
#include <qpainter.h>

#include <Graph/bp_node.h>

BP_FlowSlot::BP_FlowSlot(BP_Node *parent):BP_Slot(parent),m_showFlowName(false)
{
    trianglePolygone << QPoint(0,0) << QPoint(0,14) << QPoint(12,7);
}

QVariant BP_FlowSlot::toVariantBP()
{
    QVariantMap retMap = BP_Slot::toVariantBP().toMap() ;
    retMap["type"] = "flow" ;
    retMap["flowName"] = m_flowName;
    retMap["showFlowName"] = m_showFlowName;
    QVariantList vl;
    foreach (auto brnch, m_branches) {
        vl << brnch;
    }
    retMap["branches"] = vl;

    return retMap;
}

bool BP_FlowSlot::acceptConnection(BP_Slot *secondSlot)
{
    if(!BP_Slot::acceptConnection(secondSlot)) return false;
    auto flowSlot = dynamic_cast<BP_FlowSlot*>(secondSlot);
    if(!flowSlot) return false;
    if(isOutput() == flowSlot->isOutput())return false;

    //import the branches/threads and other info from the source
    //TODO test if it is the input or the output
    if(this->isOutput()){
        flowSlot->m_branches.append(this->branches());
        flowSlot->parentNode()->mapInputFlowToOutput();
        qDebug() << "new branches list for " << flowSlot->flowName() << " " << flowSlot->branches();
    }else{
        m_branches.append(flowSlot->branches());
        this->parentNode()->mapInputFlowToOutput();
        qDebug() << "new branches list for " << this->flowName() << " " << this->branches();
    }

    //propagate the info to the output slot of the parent


    return true;
}

void BP_FlowSlot::addBranch(int branch)
{
    m_branches.append(branch);
}

void BP_FlowSlot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::white);
    if(m_showFlowName)painter->drawText(0,9,flowName());
    painter->setBrush(Qt::white);
    if(isOutput() && m_showFlowName) painter->translate(flowNameWidth+5,0);
    painter->drawPolygon(trianglePolygone);
}

QRectF BP_FlowSlot::boundingRect() const
{
    return QRectF(0,0,20+(m_showFlowName?flowNameWidth:0),15);
}

QPointF BP_FlowSlot::getAnchorPoint()
{
    return scenePos() + QPointF(7+(m_showFlowName?flowNameWidth:0),7);
}


QString BP_FlowSlot::flowName() const
{
    return m_flowName;
}

bool BP_FlowSlot::showFlowName() const
{
    return m_showFlowName;
}

QList<int> BP_FlowSlot::branches() const
{
    return m_branches;
}


void BP_FlowSlot::setFlowName(QString flowName)
{
    if (m_flowName == flowName)
        return;

    m_flowName = flowName;

    flowNameWidth = QFontMetrics(QFont()).boundingRect(this->flowName()).width();
    //if(m_showFlowName)trianglePolygone.translate(flowNameWidth+5,0);

    emit flowNameChanged(m_flowName);
}

void BP_FlowSlot::setShowFlowName(bool showFlowName)
{
    if (m_showFlowName == showFlowName)
        return;

    m_showFlowName = showFlowName;
    emit showFlowNameChanged(m_showFlowName);
}

void BP_FlowSlot::setBranches(QList<int> branches)
{
    if (m_branches == branches)
        return;

    m_branches = branches;
    emit branchesChanged(m_branches);
}
