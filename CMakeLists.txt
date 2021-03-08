cmake_minimum_required(VERSION 3.1.0)

project(FreeCircos VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH ENV{Qt5129}/mingw73_64/lib/cmake)
#set(Qt5_DIR "D:/Apps/Qt5129/5.12.9/mingw73_64/lib/cmake")

if (CMAKE_VERSION VERSION_LESS "3.7.0")
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif ()

find_package(Qt5 COMPONENTS
    Core
    Gui
    AxContainer
    Widgets
    PrintSupport REQUIRED)

add_executable(FreeCircos
    freecircos.cpp
    freecircos.ui
    customslots.cpp
    functions.cpp
    globalsetwin.cpp
    init.cpp
    main.cpp
    addition/tablemovedialog.cpp
    circos/backbone.cpp
    circos/category.cpp
    circos/circos.cpp
    circos/gene.cpp
    circos/link.cpp
    circos/trackarrow.cpp
    component/bbwidget.cpp
    component/linkwidget.cpp
    extension/extcheckboxheaderview.cpp
    extension/extdoubleslider.cpp
    extension/extdoublesliderprivate.h
    extension/extgradientbutton.cpp
    fileprocess/excelbase.cpp
    fileprocess/qvariantlistlistmodel.cpp
    paint/colorgen.cpp
    paint/custombezier.cpp
    paint/customdonut.cpp
    paint/customlink.cpp
    paint/customlinkcanvas.cpp
    paint/customslice.cpp
    paint/customtrack.cpp
    paint/customtrackarrow.cpp
    paint/qcustomplot.cpp
    paint/smoothcurvegenerator.cpp
    resource/icon.ico
    resource/resource.qrc
    resource/thermometer.png
    tool/customtool.cpp)

include_directories(./
    ENV{Qt5129}/mingw73_64/include
    ${Qt5AxContainer_INCLUDE_DIRS}
    ${Qt5AxContainer_LIBRARIES})
add_definitions(${Qt5AxContainer_DEFINITIONS})
target_link_libraries(FreeCircos
    Qt5::Core
    Qt5::Gui
    Qt5::AxContainer
    Qt5::PrintSupport
    Qt5::Widgets)
