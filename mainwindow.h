#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Platform/Python/bp_pythonmanager.h>

#include <Modeling/importsmodel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createNewProject();

private:
    Ui::MainWindow *ui;
    BP_PythonManager *pythonTest;
    ImportsModel *m_importsModel;
    BP_ImportsItem *m_rootImportsItem;
};
#endif // MAINWINDOW_H
