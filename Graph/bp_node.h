/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef BP_NODE_H
#define BP_NODE_H

#include <QGraphicsItem>
#include <QObject>

#define RegisterNodeType(X) int X::nodeTypeID = BP_Node::setupNodeType(X::staticMetaObject);

class BP_GraphView;
class BP_CoreObject;
class BP_PlatformManager;

class BP_Node :public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_CLASSINFO("name","Node")
    Q_PROPERTY(BP_CoreObject* coreObject READ coreObject WRITE setCoreObject NOTIFY coreObjectChanged)
    Q_PROPERTY(BP_GraphView* connectedGraph READ connectedGraph WRITE setConnectedGraph NOTIFY connectedGraphChanged)

    BP_CoreObject* m_coreObject;
    BP_GraphView* m_connectedGraph;


    //TODO create node fonts

public :
    //painter members
    QRectF m_bounds;
    static int nodeCount;
    //static QMap<QString,BP_Node* (*)()> *nodesMap;
    //static QMap<QString,const QMetaObject*> *nodesMap;
    //static QList<QMetaObject> *nodeTypesList;
    //static QMetaObject* nodeTypesArray[100];
    static std::vector<QMetaObject>* nodeTypesVector;
    static int nodeTypesCount;
    int nodeId;
public:
    Q_INVOKABLE BP_Node(QObject *parent = nullptr);
    BP_Node(BP_GraphView *graphView);

    static QList<QMetaObject>* initializeNodesTypes();
    //static int setupNodeType(QString name,BP_Node* (*func)());
    static int setupNodeType(QMetaObject metaObj);
    static BP_Node* Create();

    BP_CoreObject* coreObject() const;
    BP_GraphView* connectedGraph() const;

public slots:
    void setCoreObject(BP_CoreObject* coreObject);
    void setConnectedGraph(BP_GraphView* connectedGraph);

signals:
    void coreObjectChanged(BP_CoreObject* coreObject);
    void connectedGraphChanged(BP_GraphView* connectedGraph);

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void calculateBounds();
    virtual QString renderNode(BP_PlatformManager *platform);
    virtual BP_Node* nextNode();
    virtual QString getNodeTypeString();

};

#endif // BP_NODE_H
