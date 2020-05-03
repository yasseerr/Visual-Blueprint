#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Modeling/Imports/bp_importsmoduleitem.h>
#include <Modeling/Imports/importeddelegat.h>

#include <QDebug>
#include <QDir>
#include <QPushButton>

#include <Modeling/Members/bp_memberdelegate.h>

#include <Graph/bp_graphview.h>
#include <grantlee/engine.h>
#include <grantlee/context.h>
#include <grantlee/template.h>
#include "grantlee_templates.h"
#include "grantlee_textdocument.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setting up the shortcuts
    //ui->actionopen_Node_Selection->setShortcutContext(Qt::ShortcutContext::ApplicationShortcut);

    //setting up the dock widget layount
    setCorner(Qt::BottomLeftCorner,Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner,Qt::RightDockWidgetArea);
    tabifyDockWidget(ui->messagedDockWidget,ui->consoleDockWidget);
    tabifyDockWidget(ui->modulesDockWidget,ui->importedDockWidget);

    //initializing the importedmodel
    m_impotedModel = new BP_ImportedModel();
    ui->importedListView->setModel(m_impotedModel);
    ui->importedListView->setEditTriggers(QListView::AllEditTriggers);
    ui->importedListView->setItemDelegateForColumn(0,new ImportedDelegat());
    //assign the list delegate

    //initiating imports model
    m_importsModel = new ImportsModel();
    m_importsModel->connectedView = ui->importsTreeView;
    m_rootImportsItem = new BP_ImportsItem(nullptr,this);
    m_importsModel->setRootItem(m_rootImportsItem,m_importsModel);
    ui->importsTreeView->setModel(m_importsModel);
    createNewProject();
    ui->importsTreeView->header()->setStretchLastSection(false);
    ui->importsTreeView->header()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->importsTreeView->header()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->importsTreeView->header()->resizeSection(1,60);

    //initiating members model
    m_membersModel = new BP_MembersModel(m_currentProject,ui->membersTreeView);
    ui->membersTreeView->setModel(m_membersModel);
    ui->membersTreeView->expandAll();
    ui->membersTreeView->header()->setStretchLastSection(false);
    //ui->membersTreeView->header()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->membersTreeView->header()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->membersTreeView->setItemDelegateForColumn(1,new BP_MemberDelegate(currentProject()));
    m_membersModel->m_variablesItems->createVariablesMenu(QList<QAction*>() << ui->actionAdd_Variable);

    //initiating GraphNodesModel
    m_graphNodeModel = new BP_GraphNodesModel(m_currentProject);
    //ui->tmpTreeView->setModel(m_graphNodeModel);
    m_graphNodesDialog = new GraphNodesSelectionDialog(m_graphNodeModel,this);
    m_graphNodesDialog->setCurrentProject(m_currentProject);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createNewProject()
{

    setCurrentProject(new BP_Project("Test_Project",this));
    //Loading the globlal Modules
    m_currentProject->setupPlatform();
    QStringList globalModules = currentProject()->platformManager()->listGlobalModules();
    foreach (auto moduleName, globalModules) {
        BP_ImportsModuleItem *moduleItem = new BP_ImportsModuleItem(moduleName,m_rootImportsItem,m_importsModel);
        //qDebug()<< "Module Name :" << moduleItem->m_name;
    }
    m_importsModel->setupIndexesWidgets(currentProject()->platformManager());

    //linking the imported model
    m_impotedModel->setProject(m_currentProject);


    //adding the functions tabs
    int tabIndex = ui->functionsWidget->addTab(m_currentProject->entryGraph(),"Constructor Graph");
    ui->functionsWidget->setCurrentIndex(tabIndex);
}

BP_Project *MainWindow::currentProject() const
{
    return m_currentProject;
}

void MainWindow::setCurrentProject(BP_Project *currentProject)
{
    if (m_currentProject == currentProject)
        return;
    m_currentProject = currentProject;

    m_importsModel->setConnectedProject(m_currentProject);

    emit currentProjectChanged(m_currentProject);
}


void MainWindow::on_actionAdd_Variable_triggered()
{
    m_membersModel->addMemberVariable();
}

void MainWindow::on_actionopen_Node_Selection_triggered()
{
    m_graphNodesDialog->show();
    m_graphNodesDialog->setFocus();
    //the position of the generated node is in the dialog geometry
    m_graphNodesDialog->setGeometry(QRect(QCursor::pos(),m_graphNodesDialog->geometry().size()));
    qDebug() << "it should be opened by now";
}

void MainWindow::on_actionclean_cache_triggered()
{
    m_graphNodesDialog->show();
    qDebug() << "it should be opened by now";
}

void MainWindow::on_action_Build_triggered()
{
    statusBar()->showMessage("building project ...");
    m_currentProject->platformManager()->compileProject(m_currentProject);
}
