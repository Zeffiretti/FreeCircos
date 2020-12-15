QT       += core gui axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

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
    addition/tablemovedialog.cpp \
    circos/backbone.cpp \
    circos/category.cpp \
    circos/circos.cpp \
    circos/gene.cpp \
    circos/link.cpp \
    circos/trackarrow.cpp \
    customslots.cpp \
    fileprocess/excelbase.cpp \
    fileprocess/qvariantlistlistmodel.cpp \
    functions.cpp \
    init.cpp \
    main.cpp \
    freecircos.cpp \
    paint/colorgen.cpp \
    paint/custombezier.cpp \
    paint/customdonut.cpp \
    paint/customlink.cpp \
    paint/customlinkcanvas.cpp \
    paint/customslice.cpp \
    paint/customtrack.cpp \
    paint/customtrackarrow.cpp \
    paint/qcustomplot.cpp \
    paint/smoothcurvegenerator.cpp \
    tool/customtool.cpp

HEADERS += \
    addition/tablemovedialog.h \
    circos/backbone.h \
    circos/category.h \
    circos/circos.h \
    circos/gene.h \
    circos/link.h \
    circos/trackarrow.h \
    fileprocess/excelbase.h \
    fileprocess/qvariantlistlistmodel.h \
    fileresource.h \
    freecircos.h \
    paint/colorgen.h \
    paint/custombezier.h \
    paint/customdonut.h \
    paint/customlink.h \
    paint/customlinkcanvas.h \
    paint/customslice.h \
    paint/customtrack.h \
    paint/customtrackarrow.h \
    paint/qcustomplot.h \
    paint/smoothcurvegenerator.h \
    tool/customtool.h

FORMS += \
    freecircos.ui

INCLUDEPATH += \
    $$PWD

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/resource.qrc

DISTFILES += \
    LICENSE \
    icon.rc

#RC_FILE += qrc:/icon/icon.ico
RC_ICONS = resource/icon.ico
