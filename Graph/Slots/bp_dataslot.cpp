/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_dataslot.h"

#include <QDebug>
#include <QFontMetrics>
#include <QPainter>
#include <bp_utils.h>

#include <Core/bp_parameter.h>

#include <Graph/bp_framebranch.h>
#include <Graph/bp_node.h>
#include <Graph/bp_thread.h>

#include <Widgets/graphnodesselectiondialog.h>

BP_DataSlot::BP_DataSlot(BP_Node *parent):BP_Slot(parent),m_parameterObject(nullptr),m_parameterWidth(50),
    m_showName(true),m_returnName("return"),m_requireSemaphore(false)
{
    setIsOutput(false);
    setTextColor(Qt::yellow);
    setParentNode(parent);

}

QVariant BP_DataSlot::toVariantBP()
{
    QVariantMap retMap = BP_Slot::toVariantBP().toMap() ;
    retMap["type"] = "data" ;
    retMap["parameterObject"] = m_parameterObject?m_parameterObject->toVariantBP():false;
    retMap["showName"] = m_showName;
    retMap["returnName"] = m_returnName;

    return retMap;
}

void BP_DataSlot::fromVariant(QVariant var)
{
    BP_Slot::fromVariant(var);
    auto varMap = var.toMap();
    setShowName(varMap["showName"].toBool());
    setReturnName(varMap["returnName"].toString());
    if(m_parameterObject && m_parameterObject->isImported()){
        //TODO handle the parameter objects
        qDebug() << "parameter object existe and it is imported";
    }

}

BP_Parameter *BP_DataSlot::parameterObject() const
{
    return m_parameterObject;
}

void BP_DataSlot::setParameterObject(BP_Parameter *parameterObject)
{
    if (m_parameterObject == parameterObject)
        return;

    m_parameterObject = parameterObject;
    m_parameterWidth = QFontMetrics(QFont()).boundingRect(m_parameterObject->parameterName()).width();
    emit parameterObjectChanged(m_parameterObject);
}


void BP_DataSlot::setShowName(bool showName)
{
    if (m_showName == showName)
        return;

    m_showName = showName;
    emit showNameChanged(m_showName);
}

QRectF BP_DataSlot::boundingRect() const
{
    return  QRectF(0,0,20+m_parameterWidth,20);
}

void BP_DataSlot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(textColor());
    painter->setBrush(Qt::white);
    if(isOutput()){
        if(m_showName){
            painter->drawText(0,15,returnName());
            painter->drawEllipse(QRectF(m_parameterWidth,3,16,16));
        }else {
            painter->drawEllipse(QRectF(0,3,16,16));
        }
    }else {
        //TODO add m_showName constraint when its an input
        if(m_parameterObject)
            painter->drawText(20,15,m_parameterObject->parameterName());
        else
            painter->drawText(20,15,"self");
        painter->drawEllipse(QRectF(0,3,16,16));
    }
}

QPointF BP_DataSlot::getAnchorPoint()
{
    QPoint offset;
    if(isOutput() && m_showName){
        offset.setX(m_parameterWidth+8);
        offset.setY(3+8);
    }
    else if(isOutput() && !m_showName){
        offset.setX(8);
        offset.setY(3+8);
    }
    else {
        offset.setX(8);
        offset.setY(3+8);
    }
    return this->scenePos() + offset;
}

bool BP_DataSlot::acceptConnection(BP_Slot *secondSlot)
{
    if(!BP_Slot::acceptConnection(secondSlot)) return false;
    auto dataSlot = dynamic_cast<BP_DataSlot*>(secondSlot);
    if(!dataSlot) return false;
    else if(dataSlot->isOutput() == this->isOutput()) return false;
    //TODO check the type
    if(this->isOutput()){
//        if(parentNode()->noFlowNode()){
            qDebug() << "loading the branches from the connected output slot";
            m_frameBranches << dataSlot->frameBranches();
            //if(parentNode()->noFlowNode())this->parentNode()->updateSlotsBranches(this);
            this->parentNode()->updateSlotsBranches(this);
            foreach (auto branch, this->frameBranches()) {
                qDebug() << "branches list entry (data slot) " << branch->branchID();
            }
            if(parentNode()->noFlowNode()){
                auto lcaNode = getLCAForBranches();
                //TODO update the scope of not connected nodes
                parentNode()->setScope(lcaNode?lcaNode:parentNode());
                qDebug() << "getting the LCA " << parentNode()->scope()->nodeId ;
            }
            //adding the threads reference********************************************************
            //get the threads in the branches
            auto threads = this->getJoinedThreads();
            //see if there are multiple if so insert  them to the sharedNodes
            if(threads.size()>1){
                this->setRequireSemaphore(true);
                QSet<BP_Thread*> originalThreads;
                parentNode()->getOriginalThreads(originalThreads);
                foreach (auto thread, threads) {
                    if(originalThreads.contains(thread)) continue;
                    thread->m_sharedRefsSlots.insert(this);
                }
            }else{
                this->setRequireSemaphore(false);
            }
//        }else{
//            //TODO handle outgoing dataslots flows like the output of a function
//        }
    }else{
        //TODO handle the inverse process
//        if(dataSlot->parentNode()->noFlowNode()){
            qDebug() << "loading the branches from the connected output slot";
            dataSlot->m_frameBranches << this->frameBranches();
            //if(dataSlot->parentNode()->noFlowNode())
                dataSlot->parentNode()->updateSlotsBranches(this);
            foreach (auto branch, dataSlot->frameBranches()) {
                qDebug() << "branches list entry (data slot B) " << branch->branchID();
            }
            if(dataSlot->parentNode()->noFlowNode()){
                auto lcaNode = dataSlot->getLCAForBranches();
                dataSlot->parentNode()->setScope(lcaNode);
                qDebug() << "getting the LCA " << lcaNode->nodeId ;
            }
            auto threads = dataSlot->getJoinedThreads();
            //see if there are multiple if so insert  them to the sharedNodes
            if(threads.size()>1){
                dataSlot->setRequireSemaphore(true);
                QSet<BP_Thread*> originalThreads;
                dataSlot->parentNode()->getOriginalThreads(originalThreads);
                foreach (auto thread, threads) {
                    //skip when the thread is already in the original threads of the parent node
                    // to avoid circular call for slot reference
                    if(originalThreads.contains(thread)) continue;
                    thread->m_sharedRefsSlots.insert(dataSlot);
                }
            }
            else{
                setRequireSemaphore(false);
            }
//        }
//        else{
//            //TODO handle the outgoinig dataslots like the output of a function
//        }
    }

    return true;
}

void BP_DataSlot::showNextNodeOptions(QPointF dialogPos)
{
    //show only the when the slot is an output
    if(!this->isOutput()) return;
    qDebug() << "the slot is an output ";
    if(!this->parameterObject()) return;
    auto parameterClass = this->parameterObject()->parameterClass();
    //TODO fill the parameter class when the variable only have a class name ***************
    if(! parameterClass) return;
    qDebug() << "parameter class name for dialog : " << parameterClass->name();
    //test if the node output class is valid befor showing the dialog
    BP_Utils::instance()->newNodeDialog->setRootClass(parameterClass);
    BP_Utils::instance()->newNodeDialog->setSelfSlot(this);
    BP_Utils::instance()->newNodeDialog->setGeometry(
                QRect(QCursor::pos(),BP_Utils::instance()->newNodeDialog->geometry().size()));
    BP_Utils::instance()->newNodeDialog->show();
    BP_Utils::instance()->newNodeDialog->setFocus();

}

bool BP_DataSlot::showName() const
{
    return m_showName;
}

