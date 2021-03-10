cmake_minimum_required(VERSION 3.1.0)

project(FreeCircos VERSION 0.3.0 LANGUAGES CXX)
message("CMake Info: Project: [${PROJECT_NAME}_${PROJECT_VERSION}]")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
if (NOT DEFINED ENV{Qt5_Dir})
  message(FATAL_ERROR "not defined environment variable: Qt5_Dir")
else ()
  message("Environment variable Qt5_Dir at $ENV{Qt5_Dir}")
endif ()
set(CMAKE_PREFIX_PATH $ENV{Qt5_Dir}}/mingw73_64/lib/cmake)
#set(Qt5_DIR "D:/Apps/Qt5129/5.12.9/mingw73_64/lib/cmake")
message("CMake at ${CMAKE_PREFIX_PATH}")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS
    Core
    Gui
    AxContainer
    Widgets
    PrintSupport REQUIRED)

include_directories(./)
include_directories(
    ENV{Qt5129}/mingw73_64/include
    ${Qt5AxContainer_INCLUDE_DIRS}
    ${Qt5AxContainer_LIBRARIES})
include_directories(
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Widgets_LIBRARIES})
include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Core_LIBRARIES})
include_directories(
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Gui_LIBRARIES})
include_directories(
    ${Qt5PrintSupport_INCLUDE_DIRS}
    ${Qt5PrintSupport_LIBRARIES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(ROOT_FILES
    freecircos.cpp
    freecircos.ui
    customslots.cpp
    functions.cpp
    globalsetwin.cpp
    init.cpp
    main.cpp)
set(CIRCOS_FILES
    circos/backbone.cpp
    circos/category.cpp
    circos/circos.cpp
    circos/gene.cpp
    circos/link.cpp
    circos/trackarrow.cpp)
set(ADD_FILES
    addition/tablemovedialog.cpp)
set(COMPONENT_FILES
    component/bbwidget.cpp
    component/linkwidget.cpp)
set(EXT_FILES
    extension/extcheckboxheaderview.cpp
    extension/extdoubleslider.cpp
    extension/extdoublesliderprivate.h
    extension/extgradientbutton.cpp)
set(FILEPROS_FILES
    fileprocess/excelbase.cpp
    fileprocess/qvariantlistlistmodel.cpp)
set(PAINT_FILES
    paint/colorgen.cpp
    paint/custombezier.cpp
    paint/customdonut.cpp
    paint/customlink.cpp
    paint/customlinkcanvas.cpp
    paint/customslice.cpp
    paint/customtrack.cpp
    paint/customtrackarrow.cpp
    paint/qcustomplot.cpp
    paint/smoothcurvegenerator.cpp)
set(RESOURCE_FILES
    resource/icon.ico
    resource/resource.qrc
    resource/thermometer.png)
set(TOOL_FILES
    tool/customtool.cpp)
add_executable(${PROJECT_NAME}
    ${ROOT_FILES}
    ${CIRCOS_FILES}
    ${ADD_FILES}
    ${COMPONENT_FILES}
    ${EXT_FILES}
    ${FILEPROS_FILES}
    ${PAINT_FILES}
    ${RESOURCE_FILES}
    ${TOOL_FILES})

#include(${QT_USE_FILE})
#link_directories($)
add_definitions(${Qt5AxContainer_DEFINITIONS})
target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::AxContainer
    Qt5::PrintSupport
    Qt5::Widgets)