#
# Copyright (C) 2013-2020 Mattia Basaglia
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
TEMPLATE=lib
CONFIG += dll
QT += core gui widgets
DEFINES += QTCOLORWIDGETS_LIBRARY

TARGET=QtColorWidgets

VERSION=2.2.0

OBJECTS_DIR = out/obj
MOC_DIR = out/generated
UI_DIR = out/generated
RCC_DIR = out/generated
INCLUDEPATH += $$UI_DIR $$RCC_DIR $$MOC_DIR

include(color_widgets.pri)

build_all:!build_pass {
 CONFIG -= build_all
 CONFIG += release
}

unix {
    LIB_TARGET = lib$${TARGET}.so
}
win32 {
    LIB_TARGET = $${TARGET}.dll
}

isEmpty(PREFIX) {
    PREFIX = $$OUT_PWD
}
target.path = $$OUT_PWD
DESTDIR = $$OUT_PWD/release
headers.path = $$OUT_PWD/release/include/QtColorWidgets
headers.files = $$HEADERS

INSTALLS += target headers

