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

#include <QAction>
#include <QGraphicsItem>
#include <QObject>
#include <QSet>

#define FIRST_REFERENCE "BPNodeFirstReference"
//TODO use a list of scope nodes that connect to the subbranches of this node and will be rendered before it
#define CHECK_FIRST_REFERENCE QString nodeRender = BP_Node::renderNode(platform); \
    if(nodeRender != FIRST_REFERENCE) return "";

class BP_GraphView;
class BP_CoreObject;
class BP_PlatformManager;
class BP_FrameBranch;
class BP_Slot;
class BP_Thread;
class BP_Async;
class BP_FlowSlot;

class BP_Node :public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_CLASSINFO("name","Node")
    Q_PROPERTY(BP_CoreObject* coreObject READ coreObject WRITE setCoreObject NOTIFY coreObjectChanged)
    Q_PROPERTY(BP_GraphView* connectedGraph READ connectedGraph WRITE setConnectedGraph NOTIFY connectedGraphChanged)
    Q_PROPERTY(int numberOfReferenceCalls READ numberOfReferenceCalls WRITE setNumberOfReferenceCalls NOTIFY numberOfReferenceCallsChanged)
    Q_PROPERTY(bool noFlowNode READ noFlowNode WRITE setNoFlowNode NOTIFY noFlowNodeChanged)
    Q_PROPERTY(QSet<BP_FrameBranch*> originalBranches READ originalBranches WRITE setOriginalBranches NOTIFY originalBranchesChanged)
    Q_PROPERTY(QSet<BP_FrameBranch*> subBranches READ subBranches WRITE setSubBranches NOTIFY subBranchesChanged)
    Q_PROPERTY(BP_Node* clotureNode READ clotureNode WRITE setClotureNode NOTIFY clotureNodeChanged)
    Q_PROPERTY(QList<BP_Node*> scopeNodes READ scopeNodes WRITE setScopeNodes NOTIFY scopeNodesChanged)
    Q_PROPERTY(BP_Node* scope READ scope WRITE setScope NOTIFY scopeChanged)
    Q_PROPERTY(bool bJoinWithMasterBranch READ bJoinWithMasterBranch WRITE setBJoinWithMasterBranch NOTIFY bJoinWithMasterBranchChanged)
    Q_PROPERTY(QSet<BP_FlowSlot*> awaitedAsyncSlots READ awaitedAsyncSlots WRITE setAwaitedAsyncSlots NOTIFY awaitedAsyncSlotsChanged)







protected:
    BP_Node* m_scope;
    QList<BP_Node*> m_scopeNodes;
    BP_CoreObject* m_coreObject;
    BP_GraphView* m_connectedGraph;
    bool m_bJoinWithMasterBranch;


    //TODO create node fonts
    //to not render the reference multiple times
    int m_numberOfReferenceCalls = 0;
    

    bool m_noFlowNode;

    QSet<BP_FrameBranch*> m_originalBranches;

    QSet<BP_FrameBranch*> m_subBranches;
    BP_Node* m_clotureNode;

public :

    QSet<BP_FlowSlot *> m_awaitedAsyncSlots;

    //painter members
    QRectF m_bounds;
    static int nodeCount;
    //static QMap<QString,BP_Node* (*)()> *nodesMap;
    //static QMap<QString,const QMetaObject*> *nodesMap;
    //static QList<QMetaObject> *nodeTypesList;
    //static QMetaObject* nodeTypesArray[100];
    static std::vector<QMetaObject>* nodeTypesVector;
    static int nodeTypesCount;
    static int nodeTypeID;
    int nodeId;
public:
    Q_INVOKABLE BP_Node(QObject *parent = nullptr);
    BP_Node(BP_GraphView *graphView);

    virtual void getActions(QList<QAction*> &actionsList);

    virtual QVariant toVariantBP();
    virtual void fromVariant(QVariant var);

    virtual void updateSlotsBranches(BP_Slot* slot);
    virtual void getOriginalThreads(QSet<BP_Thread*> &threadsOut);
    virtual void connectSelfSlot(BP_Slot *selfSlot);

    virtual void getOriginalAsyncs(QSet<BP_Async*> &asyncsOut);

    static QList<QMetaObject>* initializeNodesTypes();
    //static int setupNodeType(QString name,BP_Node* (*func)());
    static int setupNodeType(QMetaObject metaObj);
    static BP_Node* Create();


    BP_CoreObject* coreObject() const;
    BP_GraphView* connectedGraph() const;

public slots:
    //actions slots
    virtual QString getNodeDocumentation();

    //members slots
    void setCoreObject(BP_CoreObject* coreObject);
    void setConnectedGraph(BP_GraphView* connectedGraph);

    void setNumberOfReferenceCalls(int numberOfReferenceCalls);

    void setNoFlowNode(bool noFlowNode);

    void setOriginalBranches(QSet<BP_FrameBranch*> originalBranches);

    void setSubBranches(QSet<BP_FrameBranch*> subBranches);

    void setClotureNode(BP_Node* clotureNode);

    void setScopeNodes(QList<BP_Node*> scopeNodes);

    void setScope(BP_Node* scope);

    void setBJoinWithMasterBranch(bool bJoinWithMasterBranch);

    void setAwaitedAsyncSlots(QSet<BP_FlowSlot*> awaitedAsyncSlots);

signals:
    void coreObjectChanged(BP_CoreObject* coreObject);
    void connectedGraphChanged(BP_GraphView* connectedGraph);

    // QGraphicsItem interface
    void numberOfReferenceCallsChanged(int numberOfReferenceCalls);

    void noFlowNodeChanged(bool noFlowNode);

    void originalBranchesChanged(QSet<BP_FrameBranch*> originalBranches);

    void subBranchesChanged(QSet<BP_FrameBranch*> subBranches);

    void clotureNodeChanged(BP_Node* clotureNode);

    void scopeNodesChanged(QList<BP_Node*> scopeNodes);

    void scopeChanged(BP_Node* scope);

    void bJoinWithMasterBranchChanged(bool bJoinWithMasterBranch);

    void awaitedAsyncSlotsChanged(QSet<BP_FlowSlot*> awaitedAsyncSlots);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void calculateBounds();
    virtual QString renderNode(BP_PlatformManager *platform);
    virtual BP_Node* nextNode();
    virtual QString getNodeTypeString();
    virtual void mapInputFlowToOutput();

    int numberOfReferenceCalls() const;
    bool noFlowNode() const;
    QSet<BP_FrameBranch*> originalBranches() const;
    QSet<BP_FrameBranch*> subBranches() const;
    BP_Node* clotureNode() const;
    QList<BP_Node*> scopeNodes() const;
    BP_Node* scope() const;

    bool bJoinWithMasterBranch() const;
    QSet<BP_FlowSlot*> awaitedAsyncSlots() const;
};

#endif // BP_NODE_H
