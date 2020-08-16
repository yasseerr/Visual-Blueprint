cmake_minimum_required(VERSION 3.5)

project(VisualBlueprint LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GRANTLEE_PLUGIN_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/grantlee/5.2)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Grantlee5 REQUIRED)

#grantlee custom filters

#QT5_WRAP_CPP(MOC_BUILT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Platform/vbl_grantleelibrary.h)



#if(ANDROID)
#  add_library(Cmake_test SHARED
#    main.cpp
#    mainwindow.cpp
#    mainwindow.h
#    mainwindow.ui
#  )
#else()

#copy the platform files used by vtk
file(GLOB pythonPlatform
    ${CMAKE_SOURCE_DIR}/Platform/Python/*.py
    )
file(COPY ${pythonPlatform}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Platform/Python)
file(GLOB pythonTemplates
     ${CMAKE_SOURCE_DIR}/Platform/Python/templates/*.j2
)
file(COPY ${pythonTemplates}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Platform/Python/templates/)


file(GLOB core_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/*h
    )
file(GLOB graph_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/Links/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/Nodes/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/Nodes/Operations/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/Nodes/Threading/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/Nodes/Async/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/Slots/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/*h
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/Links/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/Nodes/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/Nodes/Operations/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/Nodes/Threading/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/Nodes/Async/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph/Slots/*.h
    )
file(GLOB modeling_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Modeling/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Modeling/Graph/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Modeling/Imports/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Modeling/Members/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Modeling/*h
    ${CMAKE_CURRENT_SOURCE_DIR}/Modeling/Graph/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Modeling/Imports/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Modeling/Members/*.h
    )
file(GLOB platform_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/bp_platformmanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/bp_platformmanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Python/bp_pythonmanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Python/bP_pythonmanager.h
    )
file(GLOB widgets_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/*.ui
    )


add_executable(VisualBlueprint
   main.cpp 
   mainwindow.cpp
   mainwindow.h
   bp_utils.h
   bp_utils.cpp
   mainwindow.ui
   resources.qrc
   ${core_sources}
   ${graph_sources}
   ${modeling_sources}
   ${platform_sources}
   ${widgets_sources}
)
#endif()

#add_library(grantlee_VBL_plugin MODULE
#  #${CMAKE_CURRENT_SOURCE_DIR}/Platform/vbl_grantleelibrary.h
#  ${CMAKE_CURRENT_SOURCE_DIR}/Platform/vbl_grantleelibrary.cpp
#  ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Python/renderimportfilter.cpp
#)
#grantlee_adjust_plugin_name(grantlee_VBL_plugin)

#target_link_libraries(grantlee_VBL_plugin
#  Grantlee5::Templates
#  Grantlee5::TextDocument
#)

#GRANTLEE FILTERS CONFIG 2
add_library(grantlee_VBL_plugin MODULE
  #${CMAKE_CURRENT_SOURCE_DIR}/Platform/vbl_grantleelibrary.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Platform/vbl_grantleelibrary.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Python/renderimportfilter.cpp
)
set_property(TARGET grantlee_VBL_plugin PROPERTY
    EXPORT_NAME vbl_plugin
)
target_link_libraries(grantlee_VBL_plugin PRIVATE
  Grantlee5::Templates
)
target_compile_features(grantlee_VBL_plugin PRIVATE
  cxx_auto_type
)
grantlee_adjust_plugin_name(grantlee_VBL_plugin)

install(TARGETS grantlee_VBL_plugin
  EXPORT grantlee_targets
  LIBRARY DESTINATION ${GRANTLEE_PLUGIN_INSTALL_DIR}
  COMPONENT Templates
)




target_link_libraries(VisualBlueprint PRIVATE Qt5::Widgets Grantlee5::Templates)


#install(TARGETS grantlee_VBL_plugin
#        RUNTIME DESTINATION ${GRANTLEE_PLUGIN_INSTALL_DIR}
#        LIBRARY DESTINATION ${GRANTLEE_PLUGIN_INSTALL_DIR}
#        ARCHIVE DESTINATION ${GRANTLEE_PLUGIN_INSTALL_DIR}
#        COMPONENT Devel
#)
