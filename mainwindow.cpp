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

    //initiating imports model
    m_importsModel = new ImportsModel();
    ui->importsTreeView->setModel(m_importsModel);
    m_importsModel->connectedView = ui->importsTreeView;
    m_rootImportsItem = new BP_ImportsItem(nullptr,this);
    m_importsModel->setRootItem(m_rootImportsItem);
    createNewProject();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createNewProject()
{
    pythonTest = new BP_PythonManager(this);
    //Loading the globlal Modules
    QStringList globalModules = pythonTest->listGlobalModules();
    foreach (auto moduleName, globalModules) {
        BP_ImportsModuleItem *moduleItem = new BP_ImportsModuleItem(moduleName,m_rootImportsItem,m_importsModel);
        qDebug()<< "Module Name :" << moduleItem->m_name;
    }
    m_importsModel->setupIndexesWidgets();
}

