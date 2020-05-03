#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Platform/Python/bp_pythonmanager.h>

#include <Modeling/importsmodel.h>

#include <Core/bp_project.h>

#include <Modeling/Imports/bp_importedmodel.h>

#include <Modeling/Members/bp_membersmodel.h>

#include <Modeling/Graph/bp_graphnodesmodel.h>

#include <Widgets/graphnodesselectiondialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(BP_Project* currentProject READ currentProject WRITE setCurrentProject NOTIFY currentProjectChanged)

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createNewProject();

    BP_Project* currentProject() const;

public slots:
    void setCurrentProject(BP_Project* currentProject);

signals:
    void currentProjectChanged(BP_Project* currentProject);

private slots:
    void on_actionAdd_Variable_triggered();

    void on_actionopen_Node_Selection_triggered();

    void on_actionclean_cache_triggered();

    void on_action_Build_triggered();

private:
    Ui::MainWindow *ui;
    ImportsModel *m_importsModel;
    BP_ImportedModel *m_impotedModel;
    BP_ImportsItem *m_rootImportsItem;
    BP_MembersModel *m_membersModel;
    BP_GraphNodesModel *m_graphNodeModel;
    GraphNodesSelectionDialog * m_graphNodesDialog;
    BP_Project* m_currentProject;
};
#endif // MAINWINDOW_H
