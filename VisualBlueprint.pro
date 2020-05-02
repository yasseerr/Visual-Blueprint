QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#adding the grantlee library

SOURCES += \
    Core/bp_class.cpp \
    Core/bp_constructor.cpp \
    Core/bp_coreobject.cpp \
    Core/bp_function.cpp \
    Core/bp_module.cpp \
    Core/bp_parameter.cpp \
    Core/bp_project.cpp \
    Core/bp_variable.cpp \
    Graph/Links/bp_flowlink.cpp \
    Graph/Links/bp_link.cpp \
    Graph/Nodes/bp_classinstancenode.cpp \
    Graph/Nodes/bp_eventnode.cpp \
    Graph/Nodes/bp_functionnode.cpp \
    Graph/Nodes/bp_intnode.cpp \
    Graph/Nodes/bp_stringnode.cpp \
    Graph/Nodes/bp_variablenode.cpp \
    Graph/Slots/bp_dataslot.cpp \
    Graph/Slots/bp_flowslot.cpp \
    Graph/bp_graphview.cpp \
    Graph/bp_node.cpp \
    Graph/bp_slot.cpp \
    Modeling/Graph/bp_graphnodeitem.cpp \
    Modeling/Graph/bp_graphnodesmodel.cpp \
    Modeling/Imports/bp_importedmodel.cpp \
    Modeling/Imports/bp_importsfunctionitem.cpp \
    Modeling/Imports/bp_importsitem.cpp \
    Modeling/Imports/bp_importsmoduleitem.cpp \
    Modeling/Imports/bp_importstypeitem.cpp \
    Modeling/Imports/bp_importsvariableitem.cpp \
    Modeling/Imports/importeddelegat.cpp \
    Modeling/Members/bp_memberdelegate.cpp \
    Modeling/Members/bp_memberitem.cpp \
    Modeling/Members/bp_membersmodel.cpp \
    Modeling/Members/bp_onevariablememberitem.cpp \
    Modeling/Members/bp_variablesmemberitem.cpp \
    Modeling/importsmodel.cpp \
    Platform/Python/bp_pythonmanager.cpp \
    Platform/bp_platformmanager.cpp \
    Widgets/graphnodesselectiondialog.cpp \
    Widgets/importeddelegatewidget.cpp \
    Widgets/importsitemwidget.cpp \
    Widgets/variableeditorwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Core/bp_class.h \
    Core/bp_constructor.h \
    Core/bp_coreobject.h \
    Core/bp_function.h \
    Core/bp_module.h \
    Core/bp_parameter.h \
    Core/bp_project.h \
    Core/bp_variable.h \
    Graph/Links/bp_flowlink.h \
    Graph/Links/bp_link.h \
    Graph/Nodes/bp_classinstancenode.h \
    Graph/Nodes/bp_eventnode.h \
    Graph/Nodes/bp_functionnode.h \
    Graph/Nodes/bp_intnode.h \
    Graph/Nodes/bp_stringnode.h \
    Graph/Nodes/bp_variablenode.h \
    Graph/Slots/bp_dataslot.h \
    Graph/Slots/bp_flowslot.h \
    Graph/bp_graphview.h \
    Graph/bp_node.h \
    Graph/bp_slot.h \
    Modeling/Graph/bp_graphnodeitem.h \
    Modeling/Graph/bp_graphnodesmodel.h \
    Modeling/Imports/bp_importedmodel.h \
    Modeling/Imports/bp_importsfunctionitem.h \
    Modeling/Imports/bp_importsitem.h \
    Modeling/Imports/bp_importsmoduleitem.h \
    Modeling/Imports/bp_importstypeitem.h \
    Modeling/Imports/bp_importsvariableitem.h \
    Modeling/Imports/importeddelegat.h \
    Modeling/Members/bp_memberdelegate.h \
    Modeling/Members/bp_memberitem.h \
    Modeling/Members/bp_membersmodel.h \
    Modeling/Members/bp_onevariablememberitem.h \
    Modeling/Members/bp_variablesmemberitem.h \
    Modeling/importsmodel.h \
    Platform/Python/bp_pythonmanager.h \
    Platform/bp_platformmanager.h \
    Widgets/graphnodesselectiondialog.h \
    Widgets/importeddelegatewidget.h \
    Widgets/importsitemwidget.h \
    Widgets/variableeditorwidget.h \
    mainwindow.h

FORMS += \
    Widgets/graphnodesselectiondialog.ui \
    Widgets/importeddelegatewidget.ui \
    Widgets/importsitemwidget.ui \
    Widgets/variableeditorwidget.ui \
    mainwindow.ui

TRANSLATIONS += \
    VisualBlueprint_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    Platform/Python/python_manager.py

INCLUDEPATH += F:/Program/Grantlee5/include
LIBS += -LF:/Program/Grantlee5/lib -lGrantlee_Templatesd -lGrantlee_TextDocumentd
