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

SOURCES += \
    Core/bp_project.cpp \
    Modeling/Imports/bp_importsfunctionitem.cpp \
    Modeling/Imports/bp_importsitem.cpp \
    Modeling/Imports/bp_importsmoduleitem.cpp \
    Modeling/importsmodel.cpp \
    Platform/Python/bp_pythonmanager.cpp \
    Platform/bp_platformmanager.cpp \
    Widgets/importsitemwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Core/bp_project.h \
    Modeling/Imports/bp_importsfunctionitem.h \
    Modeling/Imports/bp_importsitem.h \
    Modeling/Imports/bp_importsmoduleitem.h \
    Modeling/importsmodel.h \
    Platform/Python/bp_pythonmanager.h \
    Platform/bp_platformmanager.h \
    Widgets/importsitemwidget.h \
    mainwindow.h

FORMS += \
    Widgets/importsitemwidget.ui \
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
