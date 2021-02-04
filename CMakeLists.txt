cmake_minimum_required(VERSION 3.1.0)

project(QtzWidgets VERSION 0.4.0 
    DESCRIPTION "Qtz Rapid Application Development Framework, Widgets Module"
    HOMEPAGE_URL "https://github.com/soroush/qtz-widgets"
    LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Check for dependencies
find_package(Qt5 COMPONENTS Core Widgets Sql Network REQUIRED)
find_package(OpenCV CONFIG REQUIRED core imgcodecs)
if(NOT QTZ_LOCAL_BUILD)
find_package(QtzData CONFIG REQUIRED)
find_package(QtzCore CONFIG REQUIRED)
find_package(QtzSecurity CONFIG REQUIRED)
endif()

# OS-dependent sources
set(OS_SOURCES )
if(WIN32)
    list(APPEND OS_SOURCES "${PROJECT_NAME}.rc")
endif()

# Define the library
add_library (${PROJECT_NAME} SHARED
    src/application/qtz-single-application.cpp
    src/application/qtz-single-application_p.hpp
    src/i18n/localizer.cpp
    src/data/asynchronous-main-window.cpp
    src/data/date-query.cpp
    src/data/dialog-database-config.cpp
    src/data/dialog-edit-item.cpp
    src/data/dialog-edit-table.cpp
    src/data/dialog-insert-item.cpp
    src/data/i-dialog-insert-record.cpp
    src/data/numeric-query.cpp
    src/data/text-query.cpp
    src/data/widget-edit-table.cpp
    src/editors/text-editor-window.cpp
    src/editors/editable-label.cpp
    src/editors/sexagesimal-spinbox.cpp
    src/editors/jalali-date-edit.cpp
    src/viewers/image-viewer.cpp
    src/misc/choose-file.cpp
    src/misc/color-button.cpp
    src/misc/font-button.cpp
    src/editors/hex-editor-private.cpp
    src/editors/hex-editor.cpp
    src/editors/hex-editor-document/gap-buffer.cpp
    src/editors/hex-editor-document/hex-cursor.cpp
    src/editors/hex-editor-document/hex-document.cpp
    src/editors/hex-editor-document/hex-theme.cpp
    src/editors/hex-editor-document/commands/hex-command.cpp
    src/editors/hex-editor-document/commands/insert-command.cpp
    src/editors/hex-editor-document/commands/remove-command.cpp
    src/editors/hex-editor-document/commands/replace-command.cpp
    src/editors/hex-editor-document/metadata/hex-metadata.cpp
    src/editors/hex-editor-document/metadata/hex-metadata-item.cpp
    src/editors/hex-editor-paint/hex-metrics.cpp
    src/editors/hex-editor-paint/hex-painter.cpp
    # Headers
    include/qtz-widgets.hpp
    include/application/qtz-single-application.hpp
    include/i18n/localizer.hpp
    include/data/asynchronous-main-window.hpp
    include/data/date-query.hpp
    include/data/dialog-database-config.hpp
    include/data/dialog-edit-item.hpp
    include/data/dialog-edit-table.hpp
    include/data/dialog-insert-item.hpp
    include/data/filter-containter.hpp
    include/data/i-dialog-insert-record.hpp
    include/data/numeric-query.hpp
    include/data/text-query.hpp
    include/data/widget-edit-table.hpp
    include/editors/text-editor-window.hpp
    include/editors/editable-label.hpp
    include/editors/jalali-date-edit.hpp
    include/editors/sexagesimal-spinbox.hpp
    include/editors/hex-editor.hpp
    include/editors/hex-editor-private.hpp
    include/editors/hex-editor-document/gap-buffer.hpp
    include/editors/hex-editor-document/hex-cursor.hpp
    include/editors/hex-editor-document/hex-document.hpp
    include/editors/hex-editor-document/hex-theme.hpp
    include/editors/hex-editor-document/commands/hex-command.hpp
    include/editors/hex-editor-document/commands/insert-command.hpp
    include/editors/hex-editor-document/commands/remove-command.hpp
    include/editors/hex-editor-document/commands/replace-command.hpp
    include/editors/hex-editor-document/metadata/hex-metadata-item.hpp
    include/editors/hex-editor-document/metadata/hex-metadata.hpp
    include/editors/hex-editor-paint/hex-metrics.hpp
    include/editors/hex-editor-paint/hex-painter.hpp
    include/misc/choose-file.hpp
    include/misc/color-button.hpp
    include/misc/font-button.hpp
    include/security/dialog-user-login.hpp
    include/viewers/image-viewer.hpp
    # UI
    src/data/date-query.ui
    src/data/dialog-database-config.ui
    src/data/dialog-edit-table.ui
    src/data/numeric-query.ui
    src/data/text-query.ui
    src/data/widget-edit-table.ui
    src/editors/text-editor-window.ui
    src/editors/editable-label.ui
    src/misc/choose-file.ui
    src/security/dialog-user-login.ui
    ${OS_SOURCES}
)

# Set properties
set_target_properties(${PROJECT_NAME} PROPERTIES 
    PROPERTIES VERSION 0.4.0
    PROPERTIES SOVERSION 0
    CXX_STANDARD 11
    DEBUG_POSTFIX "d"
    DEFINE_SYMBOL "QTZ_WIDGETS_LIBRARY"
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link against dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt5::Core Qt5::Widgets Qt5::Sql Qt5::Network
    Qtz::QtzCore Qtz::QtzData Qtz::QtzSecurity
    opencv_core opencv_imgcodecs)

# Install and export
include(GNUInstallDirs)

export(TARGETS ${PROJECT_NAME} FILE "${PROJECT_NAME}Targets.cmake")

install(TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Targets"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY "include/" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qtz/widgets)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
    NAMESPACE Qtz::
)

install(FILES "cmake/${PROJECT_NAME}Config.cmake" 
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

# pkg-config
configure_file("${PROJECT_NAME}.pc.in" "${PROJECT_NAME}.pc" @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
