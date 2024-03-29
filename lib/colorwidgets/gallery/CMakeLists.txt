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
set (QT_SUPPORTED_VERSIONS 5)

select_qt (
  QT_SUPPORTED_VERSIONS "${QT_SUPPORTED_VERSIONS}"
  QT_DEFAULT_VERSION 5)

set (REQUIRED_QT_COMPONENTS
  Widgets
  )
find_qt (
  QT_SUPPORTED_VERSIONS "${QT_SUPPORTED_VERSIONS}"
  REQUIRED_COMPONENTS "${REQUIRED_QT_COMPONENTS}"
  OPTIONAL_COMPONENTS "")

set(SCREENSHOT_SOURCES screenshot.cpp)
set(SCREENSHOT_BINARY screenshot_bin)

add_executable(${SCREENSHOT_BINARY} EXCLUDE_FROM_ALL ${SCREENSHOT_SOURCES})

use_qt (
  TARGET_NAME ${SCREENSHOT_BINARY}
  QT_SUPPORTED_VERSIONS "${QT_SUPPORTED_VERSIONS}"
  REQUIRED_COMPONENTS "${REQUIRED_QT_COMPONENTS}"
  OPTIONAL_COMPONENTS "")
target_link_libraries(${SCREENSHOT_BINARY}
  PRIVATE
  ${COLOR_WIDGETS_LIBRARY})

add_custom_target(gallery
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${SCREENSHOT_BINARY}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${SCREENSHOT_BINARY}
)
