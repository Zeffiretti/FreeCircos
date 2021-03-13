cmake_minimum_required(VERSION 3.1.0)

project(FreeCircos VERSION 0.4.0 LANGUAGES CXX)
message("Projection Infomation: Project: [${PROJECT_NAME}_${PROJECT_VERSION}]")
if (WIN32)
  ADD_DEFINITIONS(-DWINDOWS_H_)
endif ()
if (UNIX)
  ADD_DEFINITIONS(-DUNIX_H_)
endif ()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
add_compile_definitions(QT_DEPRECATED_WARNINGS)
if (NOT DEFINED ENV{Qt5_Dir})
  message(FATAL_ERROR "not defined environment variable: Qt5_Dir")
endif ()
if (${MINGW})
  message("USING TOOLSET: MINGW")
  include_directories(./
      ENV{Qt5129}/mingw73_64/include)
  if (NOT DEFINED ENV{CMAKE_PREFIX_PATH})
    message("set CMAKE_PREFIX_PATH maunally")
    set(CMAKE_PREFIX_PATH $ENV{Qt5_Dir}/mingw73_64)
  endif ()
elseif (${MSVC})
  message("USING TOOLSET: MSVC-${MSVC_TOOLSET_VERSION}-${MSVC_VERSION}")
  include_directories(./
      ENV{Qt5129}/msvc_2017/include)
  set(CMAKE_PREFIX_PATH $ENV{Qt5_Dir}/msvc2017_64)
endif ()
#set(Qt5_DIR "D:/Apps/Qt5129/5.12.9/mingw73_64/lib/cmake")
message("CMAKE_PREFIX_PATH at ${CMAKE_PREFIX_PATH}")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS
    Core
    Gui
    AxContainer
    Widgets
    PrintSupport REQUIRED)

if (${Qt5AxContainer_FOUND})
  message("Qt5AxContainer Found Successfully.")
  add_definitions(${Qt5AxContainer_DEFINITIONS})
  include_directories(
      ${Qt5AxContainer_INCLUDE_DIRS}
      ${Qt5AxContainer_LIBRARIES})
else ()
  message(FATAL_ERROR "NO Qt5AxContainer")
endif ()
if (${Qt5Widgets_FOUND})
  message("Qt5Widgets Found Successfully.")
  add_definitions(${Qt5Widgets_DEFINITIONS})
  include_directories(
      ${Qt5Widgets_INCLUDE_DIRS}
      ${Qt5Widgets_LIBRARIES})
else ()
  message(FATAL_ERROR "NO Qt5Widgets")
endif ()
if (${Qt5Core_FOUND})
  message("Qt5Core Found Successfully.")
  add_definitions(${Qt5Core_DEFINITIONS})
  message("Qt5Core At ${Qt5Core_INCLUDE_DIRS}")
  include_directories(
      ${Qt5Core_INCLUDE_DIRS}
      ${Qt5Core_LIBRARIES})
else ()
  message(FATAL_ERROR "NO QT5Core")
endif ()
if (${Qt5Gui_FOUND})
  message("Qt5Gui Found Successfully.")
  add_definitions(${Qt5Gui_DEFINITIONS})
  include_directories(
      ${Qt5Gui_INCLUDE_DIRS}
      ${Qt5Gui_LIBRARIES})
else ()
  message(FATAL_ERROR "No Qt5Core")
endif ()
if (${Qt5PrintSupport_FOUND})
  message("Qt5PrintSupport Found Successfully.")
  add_definitions(${Qt5PrintSupport_DEFINITIONS})
  include_directories(
      ${Qt5PrintSupport_INCLUDE_DIRS}
      ${Qt5PrintSupport_LIBRARIES})
else ()
  message(FATAL_ERROR "NO Qt5PrintSupport")
endif ()
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(ICON_FILE icon.rc)
set(ROOT_FILES
    freecircos.cpp
    freecircos.ui
    customslots.cpp
    functions.cpp
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
    component/linkwidget.cpp
    component/globalsetwin.cpp)
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
    ${ICON_FILE}
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

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::AxContainer
    Qt5::PrintSupport
    Qt5::Widgets)

message("Build Type: ${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE MATCHES Release)
  message("Release Project")
  add_definitions(-DQT_NO_DEBUG_OUTPUT)
  target_compile_definitions(${PROJECT_NAME} PUBLIC QT_NO_DEBUG_OUTPUT)
endif ()
