#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Modeling/Imports/bp_importsmoduleitem.h>

#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setting up the dock widget layount
    setCorner(Qt::BottomLeftCorner,Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner,Qt::RightDockWidgetArea);
    tabifyDockWidget(ui->messagedDockWidget,ui->consoleDockWidget);
    tabifyDockWidget(ui->modulesDockWidget,ui->importedDockWidget);

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createNewProject()
{

    setCurrentProject(new BP_Project("Test Project",this));
    //Loading the globlal Modules
    m_currentProject->setupPlatform();
    QStringList globalModules = currentProject()->platformManager()->listGlobalModules();
    foreach (auto moduleName, globalModules) {
        BP_ImportsModuleItem *moduleItem = new BP_ImportsModuleItem(moduleName,m_rootImportsItem,m_importsModel);
        //qDebug()<< "Module Name :" << moduleItem->m_name;
    }
    m_importsModel->setupIndexesWidgets(currentProject()->platformManager());
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

