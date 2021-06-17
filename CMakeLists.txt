cmake_minimum_required(VERSION 3.1.0)

project(FreeCircos LANGUAGES CXX)
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 6)
set(${PROJECT_NAME}_VERSION_PATCH 2)
set(PROJECT_VERSION ${${PROJECT_NAME}_VERSION_MAJOR}_${${PROJECT_NAME}_VERSION_MINOR})
message("Projecte Infomation: [${PROJECT_NAME}_${PROJECT_VERSION}]")
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
message("PROJECT_BINARY at ${PROJECT_BINARY_DIR}")
#     静态库输出目录 => 构建目录/lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
#     动态库输出目录 => 构建目录/bin
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
#     可执行程序输出目录 => 构建目录/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
add_compile_definitions(QT_DEPRECATED_WARNINGS)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/colorwidgets)

if (NOT DEFINED ENV{Qt5_Dir})
  message(FATAL_ERROR "not defined environment variable: Qt5_Dir")
endif ()
if (${MINGW})
  message("USING TOOLSET: MINGW")
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ENV{Qt5129}/mingw73_64/include)
  if (NOT DEFINED CMAKE_PREFIX_PATH)
    message("set CMAKE_PREFIX_PATH maunally")
    list(APPEND CMAKE_PREFIX_PATH "$ENV{Qt5_Dir}/mingw73_64")
  endif (NOT DEFINED CMAKE_PREFIX_PATH)
elseif (${MSVC})
  message("USING TOOLSET: MSVC-${MSVC_TOOLSET_VERSION}-${MSVC_VERSION}")
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ ENV{Qt5129}/msvc_2017/include)
  if (NOT DEFINED CMAKE_PREFIX_PATH)
    list(APPEND CMAKE_PREFIX_PATH "$ENV{Qt5_Dir}/msvc2017_64")
  endif (NOT DEFINED CMAKE_PREFIX_PATH)
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
if (${Qt5Widgets_FOUND})
  message("Qt5Widgets Found Successfully.")
  add_definitions(${Qt5Widgets_DEFINITIONS})
  include_directories(
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Widgets_LIBRARIES})
else ()
  message(FATAL_ERROR "NO Qt5Widgets")
endif ()
if (${QtColorWidgets_FOUND})
  message("QtColorWidgets Found Successfully.")
  include_directories(${QtColorWidgets_INCLUDE_DIRS})
else ()
  message(FATAL_ERROR "No QtColorWidgets")
endif ()
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(ADD_FILES
  addition/tablemovedialog.cpp)
set(CIRCOS_FILES
  circos/backbone.cpp
  circos/category.cpp
  circos/circos.cpp
  circos/gene.cpp
  circos/link.cpp
  circos/trackarrow.cpp)
set(COMPONENT_FILES
  component/bbwidget.cpp
  component/linkwidget.cpp
  component/globalsetwin.cpp
  component/colorwidget.cpp
  component/arrowwidget.cpp component/radiuswidget.cpp)
set(EXT_FILES
  extension/extcheckboxheaderview.cpp
  extension/extdoubleslider.cpp
  extension/extdoublesliderprivate.h
  extension/extgradientbutton.cpp
  extension/extcolordialog.cpp
  extension/extitemmodel.cpp
  extension/exttableview.cpp
  extension/extarroweditor.cpp extension/extsymslider.cpp extension/extsymslider.h extension/extsorttable.cpp extension/extsorttable.h)
set(FILEPROS_FILES
  fileprocess/excelbase.cpp
  fileprocess/qvariantlistlistmodel.cpp)
set(ICON_FILE icon.rc)
set(PAINT_FILES
  paint/colorgen.cpp
  paint/custombezier.cpp
  paint/customdonut.cpp
  paint/customlink.cpp
  paint/customlinkcanvas.cpp
  paint/customslice.cpp
  paint/customtrack.cpp
  paint/customtrackarrow.cpp
  paint/qcustomplot.cpp)
set(RESOURCE_FILES
  resource/icon.ico
  resource/resource.qrc
  resource/thermometer.png)
set(ROOT_FILES
  freecircos.cpp
  freecircos.ui
  customslots.cpp
  functions.cpp
  init.cpp
  main.cpp)
set(TOOL_FILES
  tool/customtool.cpp)


if (CMAKE_BUILD_TYPE MATCHES Release)
  add_executable(${PROJECT_NAME} WIN32
    ${ADD_FILES}
    ${CIRCOS_FILES}
    ${COMPONENT_FILES}
    ${EXT_FILES}
    ${FILEPROS_FILES}
    ${ICON_FILE}
    ${PAINT_FILES}
    ${RESOURCE_FILES}
    ${ROOT_FILES}
    ${TOOL_FILES})
elseif (CMAKE_BUILD_TYPE MATCHES Debug)
  add_executable(${PROJECT_NAME}
    ${ADD_FILES}
    ${CIRCOS_FILES}
    ${COMPONENT_FILES}
    ${EXT_FILES}
    ${FILEPROS_FILES}
    ${ICON_FILE}
    ${PAINT_FILES}
    ${RESOURCE_FILES}
    ${ROOT_FILES}
    ${TOOL_FILES})
endif ()
target_link_libraries(${PROJECT_NAME}
  Qt5::Core
  Qt5::Gui
  Qt5::AxContainer
  Qt5::PrintSupport
  Qt5::Widgets)
link_directories(lib/colorwidgets)

target_link_libraries(${PROJECT_NAME} QtColorWidgets)
add_dependencies(${PROJECT_NAME} QtColorWidgets)
message("Build Type: ${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE MATCHES Release)
  message("Release Project")
  #  add_definitions(-DQCUSTOMPLOT_USE_OPENGL)
  target_compile_definitions(${PROJECT_NAME} PUBLIC QT_NO_DEBUG_OUTPUT)
endif ()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
