/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_pythonmanager.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <bp_utils.h>

#include <Core/bp_project.h>

#include <Graph/bp_framebranch.h>
#include <Graph/bp_graphview.h>
#include <Graph/bp_node.h>
#include <Graph/bp_thread.h>

#include <Graph/Nodes/bp_addnode.h>
#include <Graph/Nodes/bp_boolnode.h>
#include <Graph/Nodes/bp_classinstancenode.h>
#include <Graph/Nodes/bp_eventnode.h>
#include <Graph/Nodes/bp_floatnode.h>
#include <Graph/Nodes/bp_functionnode.h>
#include <Graph/Nodes/bp_ifnode.h>
#include <Graph/Nodes/bp_intnode.h>
#include <Graph/Nodes/bp_loopnode.h>
#include <Graph/Nodes/bp_stringnode.h>

#include <Graph/Links/bp_link.h>

#include <Graph/Slots/bp_flowslot.h>

#include <Graph/Nodes/Threading/bp_createthreadsnode.h>

BP_PythonManager::BP_PythonManager(QObject *parent):BP_PlatformManager(parent)
{
    m_language = "python";
    m_framwork = "standard";
    m_compilerPath = "F:/Program Files/WPy64-3720/python-3.7.2.amd64/python.exe";
    m_managerFile = "./Platform/Python/python_manager.py";
    m_managerProcess.setProgram(m_compilerPath);
    m_runningProcess.setProgram(m_compilerPath);
//    QObject::connect(&m_managerProcess,&QProcess::readyReadStandardOutput,this,&BP_PythonManager::standardOutputReady);
//    QObject::connect(&m_managerProcess,&QProcess::readyReadStandardError,this,&BP_PythonManager::errorOutputReady);

    //setting the symbols
    defaultOperationSymbols["addition"]="+";
    defaultOperationSymbols["substraction"]="-";
    defaultOperationSymbols["multiplication"]="*";
    defaultOperationSymbols["division"]="/";
    defaultOperationSymbols["and"]="and";
    defaultOperationSymbols["or"]="or";
    defaultOperationSymbols["not"]="!";
    defaultOperationSymbols["xor"]="^";
}

QStringList BP_PythonManager::listGlobalModules()
{
    QStringList returnList;

    m_managerProcess.setArguments(QStringList() << m_managerFile << "listGM");
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    QJsonArray listJson = QJsonDocument::fromJson(listRawData).array();
    foreach (auto item, listJson) {
        returnList << item.toString();
        //qDebug() << item.toString();
    }
    return returnList;
}

void BP_PythonManager::loadBuiltins(BP_Project *project)
{
    QStringList returnList;

    m_managerProcess.setArguments(QStringList() << m_managerFile << "loadBuiltins");
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    QJsonArray listJson = QJsonDocument::fromJson(listRawData).array();
    auto builtinsList = listJson.toVariantList();
    foreach (auto builtinVariant, builtinsList ) {
        QVariantMap builinMap = builtinVariant.toMap();
        //TODO collapse to getCoreObjectFromVariant
        if(builinMap.value("type").toString() == "func"){
            BP_Function *builtinFunc = new BP_Function(&builinMap,project);
            builtinFunc->setImportHiearchy(QStringList() << builtinFunc->name() << "builtins");
            project->addBuiltin(builtinFunc);
        }
        else if(builinMap.value("type").toString() == "var"){
            BP_Variable *builtinVar = new BP_Variable(&builinMap,project);
            builtinVar->setImportHiearchy(QStringList() << builtinVar->name() << "builtins");
            project->addBuiltin(builtinVar);
        }
        else if(builinMap.value("type").toString() == "class"){
            BP_Class *builtinClass = new BP_Class(&builinMap,project);
            builtinClass->setImportHiearchy(QStringList() << builtinClass->name() << "builtins");
            project->addBuiltin(builtinClass);
        }

    }
}

QList<QPair<QString, QString>> BP_PythonManager::inspectModuleByName(QStringList moduleHierachy)
{
    QList<QPair<QString,QString>> retList;
    m_managerProcess.setArguments(QStringList() << m_managerFile << "inspectModule" << moduleHierachy);
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    //qDebug() << listRawData;
    qDebug() << m_managerProcess.readAllStandardError();
    QJsonArray listJson = QJsonDocument::fromJson(listRawData).array();
    foreach (auto item, listJson) {
        QPair<QString,QString> importInfo;
        importInfo.first = item.toObject().value("name").toString();
        importInfo.second = item.toObject().value("type").toString();
        retList << importInfo;
        //qDebug() << retList;
    }
    return retList;
}

QVariantMap BP_PythonManager::importModule(QStringList moduleHiearchy)
{
    m_managerProcess.setArguments(QStringList() << m_managerFile << "importModule" << moduleHiearchy);
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    qDebug() <<  listRawData;
    qDebug() << m_managerProcess.readAllStandardError();
    //QJsonParseError jsonError;
    QJsonObject jsonObject = QJsonDocument::fromJson(listRawData).object();
    //qDebug() << jsonError.errorString() << jsonError.offset;
    return jsonObject.toVariantMap();
}

QVariantMap BP_PythonManager::importFunction(QStringList moduleHiearchy)
{
    m_managerProcess.setArguments(QStringList() << m_managerFile << "importFunction" << moduleHiearchy);
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    qDebug() << listRawData.size();
    qDebug() << m_managerProcess.readAllStandardError();
    QJsonObject jsonObject = QJsonDocument::fromJson(listRawData).object();
    return jsonObject.toVariantMap();
}

QVariantMap BP_PythonManager::importVariable(QStringList moduleHiearchy)
{
    qDebug() << "Variable Module Hiearchy > " << moduleHiearchy;
    m_managerProcess.setArguments(QStringList() << m_managerFile << "importVariable" << moduleHiearchy);
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    //qDebug() << listRawData;
    qDebug() << m_managerProcess.readAllStandardError();
    QJsonObject jsonObject = QJsonDocument::fromJson(listRawData).object();
    return jsonObject.toVariantMap();
}

QVariantMap BP_PythonManager::importClass(QStringList moduleHiearchy)
{
    qDebug() << "Class Module Hiearchy > " << moduleHiearchy;
    m_managerProcess.setArguments(QStringList() << m_managerFile << "importClass" << moduleHiearchy);
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    //qDebug() << listRawData;
    qDebug() << m_managerProcess.readAllStandardError();
    QJsonObject jsonObject = QJsonDocument::fromJson(listRawData).object();
    return jsonObject.toVariantMap();
}

void BP_PythonManager::compileProject(BP_Project *project)
{
    //rendering the imports
    auto projectTemplate = grantleeEngine->loadByName("Python/templates/project.j2");
    QVariantHash mapping ;
    mapping.insert("project",QVariant::fromValue(project));
    //initiating the members
    QStringList members;
    QStringList membersLock;
    foreach (auto member, project->memberVariables()) {
        //TODO support lists
        //TODO support primitives
        members << "self."+member->name()+" = "+member->className()+"()";
        QSet<BP_Thread*> memberThreads;
        foreach(auto branch,member->connectedBranches()){
            memberThreads.unite(branch->threads());
        }
        qDebug() << "the size of threads for the member object > " << memberThreads.size();
        if(memberThreads.size()>1)
            membersLock << "self."+member->name()+"_lock = threading.Lock()";
    }
    mapping.insert("members",members);
    mapping.insert("members_lock",membersLock);

    //filing the init function with entryGraph content
    QStringList mainCodeList;
    BP_Node *currentCompilationNode = project->entryGraph()->entryNode();
    while (currentCompilationNode) {
        QString nodeRenderedCode = currentCompilationNode->renderNode(this);
        mainCodeList << nodeRenderedCode;
        currentCompilationNode = currentCompilationNode->nextNode();
    }
    mapping.insert("mainCodeList",mainCodeList);

    //adding the member functions
    mapping.insert("member_functions",QStringList(memberFunctionsMap.values()));

    Grantlee::Context c(mapping);

    QString generatedCode = projectTemplate->render(&c);
    qDebug() << generatedCode.toUtf8();

    //saving to file
    QDir compilationDir = QApplication::applicationDirPath();
    if(!compilationDir.exists("Compilation")) compilationDir.mkdir("Compilation");
    compilationDir.cd("Compilation");

    QFile outputFile(compilationDir.path()+"/"+project->projectName()+".py");
    outputFile.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream ts(&outputFile);
    ts << generatedCode;
    outputFile.close();

    clearCompilationVariables(project);
}

QStringList BP_PythonManager::compileBlock(BP_Node *startNode, BP_Node *endNode)
{
    QStringList blockCodeList;
    BP_Node *currentCompilationNode = startNode;
    while (currentCompilationNode != endNode && currentCompilationNode != nullptr) {
        //TODO check that the loop is not infinite
        QString nodeRenderedCode = currentCompilationNode->renderNode(this);
        blockCodeList << nodeRenderedCode;
        currentCompilationNode = currentCompilationNode->nextNode();
        //if(currentCompilationNode==endNode)currentCompilationNode=nullptr;
    }
    return blockCodeList;
}

QString BP_PythonManager::appendMemberFunction(BP_Node *startNode, QString functionName,QStringList args)
{
    auto functionBlockRendered = compileBlock(startNode,nullptr);


    auto projectTemplate = grantleeEngine->loadByName("Python/templates/MemberFunction.j2");
    QVariantHash mapping ;
    mapping.insert("function_name",functionName);
    mapping.insert("function_block",functionBlockRendered);
    mapping.insert("args",args);

    Grantlee::Context c(mapping);
    QString functionRendered =  projectTemplate->render(&c);
    memberFunctionsMap.insert(functionName,functionRendered);
    return functionRendered;
}

void BP_PythonManager::runProject(BP_Project *project)
{
    compileProject(project);
    QString projectFilePath = "./Compilation/"+project->projectName()+".py";
    m_runningProcess.setArguments(QStringList() << "-u" << projectFilePath);
    m_runningProcess.setProcessChannelMode(QProcess::MergedChannels);
    //m_runningProcess.setReadChannelMode(QProcess::ProcessChannelMode::SeparateChannels);
    connect(&m_runningProcess,&QProcess::readyReadStandardOutput,[this](){
        //BP_Utils::logPlainText("recerinving signal");
        QByteArray executionOutput =  m_runningProcess.readAllStandardOutput();
        //TODO receive commands
        if(executionOutput.size()>0)BP_Utils::logPlainText(executionOutput);
    });
    connect(&m_runningProcess,&QProcess::readyReadStandardError,[this](){
        QByteArray errorData  = m_runningProcess.readAllStandardError();
        if(errorData.size()>0)BP_Utils::log(errorData,"PythonManager",BP_Utils::Error);
    });

//    connect(&m_runningProcess,&QProcess::bytesWritten,[this](){
//        BP_Utils::logPlainText("recerinving signal");
//        QByteArray executionOutput =  m_runningProcess.r;
//        //TODO receive commands
//        if(executionOutput.size()>0)BP_Utils::logPlainText(executionOutput);
//    });
    m_runningProcess.start();
    //m_runningProcess.waitForReadyRead();
    //m_runningProcess.waitForFinished();
    //QByteArray executionOutput =  m_runningProcess.readAllStandardOutput();
    //if(executionOutput.size()>0)BP_Utils::logPlainText(executionOutput);//BP_Utils::log(executionOutput,"PythonManager",BP_Utils::Info);
//    QByteArray errorData  = m_managerProcess.readAllStandardError();
//    if(errorData.size()>0)BP_Utils::log(errorData,"PythonManager",BP_Utils::Error);
}

void BP_PythonManager::clearCompilationVariables(BP_Project *project)
{
    //TODO clear the data in the other graphes
    foreach (auto node, project->entryGraph()->nodes()) {
        node->setNumberOfReferenceCalls(0);
    }
}

QString BP_PythonManager::renderEventNode(BP_EventNode *node)
{
    return "#this is a event placeholder\n"+renderScopeNodes(node);
}

QString BP_PythonManager::renderFunctionNode(BP_FunctionNode *node)
{
    //return "this is a function placeholder";
    //rendering the variables nodes
    QStringList functionInputsDeclaration;
    QStringList requiredSemaphores;
    foreach (auto inputSlot, node->inputParameters()) {
        if(inputSlot->connectedLinks().size()>0){
            auto sourceSlot = inputSlot->connectedLinks().first()->inSlot();
            QString renderedParameter = sourceSlot->parentNode()->renderNode(this);
            if(renderedParameter!="")functionInputsDeclaration << renderedParameter;
            auto sourceDataSlot = qobject_cast<BP_DataSlot*>(sourceSlot);
            if(sourceDataSlot && sourceDataSlot->requireSemaphore()) requiredSemaphores << sourceDataSlot->reference()+"_lock";
        }
    }

    auto projectTemplate = grantleeEngine->loadByName("Python/templates/Function.j2");
    QVariantHash mapping ;
    mapping.insert("function",QVariant::fromValue(node));
    mapping.insert("functionInputsDeclaration",functionInputsDeclaration);
    mapping.insert("required_semaphores",requiredSemaphores);
    mapping.insert("return_require_semaphore",node->returnSlot()->requireSemaphore());

    //temporary solution for parameter refrences
    QStringList parameterRefrences;
    foreach (auto paramSlot, node->inputParameters()) {
        //TODO support multipe links
        //TODO handle the different type of links
        if(paramSlot->connectedLinks().size()>0){
            parameterRefrences << paramSlot->connectedLinks().first()->inSlot()->reference();
        }
    }

    mapping.insert("parameterRefrences",parameterRefrences);

    Grantlee::Context c(mapping);
    return projectTemplate->render(&c);
}

QString BP_PythonManager::renderIntegerNode(BP_IntNode *node)
{
    QString retString = "";
    if(node->outputSlot()->requireSemaphore()) retString += node->outputSlot()->reference()+"_lock = threading.Lock()\n";
    retString += node->outputSlot()->reference()+" = "+QString::number(node->variableObject()->value().toInt());
    return retString;
}

QString BP_PythonManager::renderFloatNode(BP_FloatNode *node)
{
    QString retString = "";
    if(node->outputSlot()->requireSemaphore()) retString += node->outputSlot()->reference()+"_lock = threading.Lock()\n";
    retString += node->variableObject()->name()  + " = " + QString::number(node->variableObject()->value().toFloat());
    return retString;
}

QString BP_PythonManager::renderStringNode(BP_StringNode *node)
{
    QString retString = "";
    if(node->outputSlot()->requireSemaphore()) retString += node->outputSlot()->reference()+"_lock = threading.Lock()\n";
    retString += node->variableObject()->name()  + " = \"" + node->variableObject()->value().toString()+"\"";
    return retString;
}

QString BP_PythonManager::renderBoolNode(BP_BoolNode *node)
{
    QString retString = "";
    if(node->outputSlot()->requireSemaphore()) retString += node->outputSlot()->reference()+"_lock = threading.Lock()\n";
    //making the first value uppercase
    retString += node->variableObject()->name() + " = " + (node->variableObject()->value().toBool()?"True":"False");
    return retString;
}

QString BP_PythonManager::renderClassInstanceNode(BP_ClassInstanceNode *node)
{
    //return "this is a function placeholder";
    //rendering the variables nodes
    QStringList instanceInputsDeclaration;
    QStringList semaphores;
    foreach (auto inputSlot, node->inputParameters()) {
        if(inputSlot->connectedLinks().size()>0){
            auto sourceSlot = inputSlot->connectedLinks().first()->inSlot();
            QString renderedParameter = sourceSlot->parentNode()->renderNode(this);
            if(renderedParameter!="")instanceInputsDeclaration << renderedParameter;
            auto sourceDataSlot = qobject_cast<BP_DataSlot*>(sourceSlot);
            if(sourceDataSlot && sourceDataSlot->requireSemaphore()) semaphores << sourceDataSlot->reference()+"_lock";
        }
    }

    auto projectTemplate = grantleeEngine->loadByName("Python/templates/ClassInstance.j2");
    QVariantHash mapping ;
    mapping.insert("instance",QVariant::fromValue(node));
    mapping.insert("instanceInputsDeclaration",instanceInputsDeclaration);
    mapping.insert("returnName",node->outputSlot()->reference());
    mapping.insert("semaphores",semaphores);
    mapping.insert("require_semaphore",node->outputSlot()->requireSemaphore());

    //temporary solution for parameter refrences
    QStringList parameterRefrences;
    foreach (auto paramSlot, node->inputParameters()) {
        //TODO support multipe links
        //TODO handle the different type of links
        if(paramSlot->connectedLinks().size()>0){
            parameterRefrences << paramSlot->connectedLinks().first()->inSlot()->reference();
        }
    }

    mapping.insert("parameterRefrences",parameterRefrences);

    Grantlee::Context c(mapping);
    return projectTemplate->render(&c);
    //return "";
}

QString BP_PythonManager::renderIFStatement(BP_IFNode *node)
{
    //render scope nodes
    auto scopeNodes  = renderScopeNodes(node);
    //render the condition
    auto booleanSourceSlot = node->booleanSlot()->connectedLinks().first()->inSlot();
    QString conditionRendered =  booleanSourceSlot->parentNode()->renderNode(this);
    QString conditionReference = booleanSourceSlot->reference();

    qDebug() << "compiling an if statement" ;
    //qDebug() <<  "condition : " << conditionRendered;
    //qDebug() << "reference :" << conditionReference;

    //TODO add a condition when the else is not present
    auto nextNode = node->nextNode();

    //render the true branch
    auto startNode = node->trueFlowSlot()->connectedLinks().first()->outSlot()->parentNode();
    auto trueBlock = compileBlock(startNode,nextNode);

    //qDebug() << "true block " << trueBlock;
    // render the false branch
    auto startNodeF = node->falseFlowSlot()->connectedLinks().first()->outSlot()->parentNode();
    auto falseBlock = compileBlock(startNodeF,nextNode);
    //qDebug() << "false block " << falseBlock;

    // insert the result to the template
    auto projectTemplate = grantleeEngine->loadByName("Python/templates/IFStatement.j2");
    QVariantHash mapping ;
    mapping.insert("condition_declaration",conditionRendered);
    mapping.insert("condition_reference",conditionReference);
    mapping.insert("true_block",trueBlock);
    mapping.insert("false_block",falseBlock);
    mapping.insert("scope_nodes",scopeNodes);
    mapping.insert("boolean_require_lock",qobject_cast<BP_DataSlot*>(booleanSourceSlot)->requireSemaphore());

    // polish the results
    Grantlee::Context c(mapping);
    return projectTemplate->render(&c);
}

QString BP_PythonManager::renderLoopStatement(BP_LoopNode *node)
{
    //render scope nodes
    auto scopeNodes  = renderScopeNodes(node);
    QList<BP_Slot*> loopInputList;
    loopInputList << node->startValueSlot() << node->endValueSlot() << node->stepSlot();
    QStringList loopInputsDeclaration;
    QStringList loopInputReferences;
    QStringList semaphores;

    //rendering inputs
    //TODO render the references
    foreach (auto inputSlot, loopInputList) {
        auto inputSlotSource = qobject_cast<BP_DataSlot*>(inputSlot->connectedLinks().first()->inSlot());
        loopInputsDeclaration << inputSlotSource->parentNode()->renderNode(this);
        loopInputReferences << inputSlotSource->reference();
        if(inputSlot && inputSlotSource->requireSemaphore() && !semaphores.contains(inputSlotSource->reference()+"_lock"))
            semaphores << inputSlotSource->reference()+"_lock";
    }

    auto loopBlockEntryNode = node->loopFlowSlot()->connectedLinks().first()->outSlot()->parentNode();
    auto loopBlockCompilation = compileBlock(loopBlockEntryNode,nullptr);

    auto projectTemplate = grantleeEngine->loadByName("Python/templates/LoopStatement.j2");
    QVariantHash mapping ;
    mapping.insert("loopInputsDeclaration",loopInputsDeclaration);
    mapping.insert("counter_name",node->counterSlot()->reference());
    mapping.insert("start",loopInputReferences[0]);
    mapping.insert("end",loopInputReferences[1]);
    mapping.insert("step",loopInputReferences[2]);
    mapping.insert("loop_block",loopBlockCompilation);
    mapping.insert("scope_nodes",scopeNodes);
    mapping.insert("semaphores",semaphores);
    mapping.insert("counter_require_semaphore",node->counterSlot()->requireSemaphore());

    Grantlee::Context c(mapping);
    return projectTemplate->render(&c);
}

QString BP_PythonManager::renderCreateThreadsNode(BP_CreateThreadsNode *node)
{
    QString threadFunctionName = "function_thread_slot_"+QString::number(node->subThreadsSlots().first()->slotID);
    //TODO foreach slot run the thread and create the thread function

    //add the shared references
    QStringList slotsReferences;
    QStringList slotsSemaphores;
    //TODO apply it to all the threads in the node, not just the first
    foreach (auto refSlot, node->slotsToThreadMap.values().first()->sharedRefsSlots()) {
        slotsReferences << refSlot->reference();
        auto refSlotData = qobject_cast<BP_DataSlot*>(refSlot);
        if(refSlotData && refSlotData->requireSemaphore()) slotsReferences << refSlotData->reference()+"_lock";
        qDebug() << "adding reference to the thread args " << refSlot->reference();
        //TODO add the semaphore when required
    }
    appendMemberFunction(node->subThreadsSlots().first()->connectedLinks().first()->outSlot()->parentNode(),
                                          threadFunctionName,slotsReferences+slotsSemaphores);


    auto projectTemplate = grantleeEngine->loadByName("Python/templates/CreateThreads.j2");
    QVariantHash mapping ;
    mapping.insert("function_name",threadFunctionName);
    mapping.insert("args",slotsReferences+slotsSemaphores);

    Grantlee::Context c(mapping);
    return  projectTemplate->render(&c);

}

QString BP_PythonManager::renderDefaultOperationTool(BP_OperationToolNode *node, QString operationName)
{
    QString symbol = defaultOperationSymbols[operationName];
    //render the inputs
    //rendering the variables nodes
    QStringList inputs;
    QStringList semaphores;
    foreach (auto inputSlot, node->inputSlots()) {
        if(inputSlot->connectedLinks().size()>0){
            auto sourceSlot = inputSlot->connectedLinks().first()->inSlot();
            QString renderedParameter = sourceSlot->parentNode()->renderNode(this);
            if(renderedParameter!="")inputs << renderedParameter;
            auto sourceDataSlot = qobject_cast<BP_DataSlot*>(sourceSlot);
            if(sourceDataSlot && sourceDataSlot->requireSemaphore()) semaphores << sourceDataSlot->reference()+"_lock";
        }
    }

    auto projectTemplate = grantleeEngine->loadByName("Python/templates/Operation.j2");
    QVariantHash mapping ;
    mapping.insert("inputs",inputs);
    mapping.insert("reference",node->outputSlot()->reference());
    mapping.insert("semaphores",semaphores);
    mapping.insert("require_semaphore",node->outputSlot()->requireSemaphore());

    //generating senetense
    // getting the references
    QStringList parameterRefrences;
    foreach (auto paramSlot, node->inputSlots()) {
        //TODO support multipe links
        //TODO handle the different type of links
        if(paramSlot->connectedLinks().size()>0){
            parameterRefrences << paramSlot->connectedLinks().first()->inSlot()->reference();
        }
    }
    QString sentence = "None";
    if(parameterRefrences.size()>1){
        sentence = parameterRefrences.join(" "+symbol+"");
    }
    else if(parameterRefrences.size()==1){
        sentence = symbol+parameterRefrences.first();
    }
    mapping.insert("sentence",sentence);
    Grantlee::Context c(mapping);
    return projectTemplate->render(&c);
}

QString BP_PythonManager::renderScopeNodes(BP_Node *node)
{
    QString returnString;
    foreach (auto scopeNode, node->scopeNodes()) {
        returnString += scopeNode->renderNode(this) + "\n";
    }
    return returnString;
}

QString BP_PythonManager::getDocForCoreObject(BP_CoreObject *obj)
{
    if(!obj->isImported()) return "<i> object is not importd, cant load doc</i>";
    m_managerProcess.setArguments(QStringList() << m_managerFile << "getDoc" << obj->importHiearchy());
    m_managerProcess.start();
    m_managerProcess.waitForFinished();
    QByteArray listRawData =  m_managerProcess.readAllStandardOutput().mid(12);
    qDebug() << "documentation size" << listRawData.size() << listRawData;
    qDebug() << m_managerProcess.readAllStandardError();
    return listRawData;
}


void BP_PythonManager::standardOutputReady()
{
    qDebug() << "Data Ready : " << m_managerProcess.readAllStandardOutput();
}

void BP_PythonManager::errorOutputReady()
{
    qDebug() << "Error Ready : " << m_managerProcess.readAllStandardError();
}
