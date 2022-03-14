cmake_minimum_required(VERSION 3.19.0)

project(QtzWidgets VERSION 0.4.0 
    DESCRIPTION "Qtz Rapid Application Development Framework, Widgets Module"
    HOMEPAGE_URL "https://github.com/soroush/qtz-widgets"
    LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Check for dependencies
find_package(Qt5 COMPONENTS Core Widgets Sql Network REQUIRED)
find_package(OpenCV CONFIG REQUIRED)

if(NOT QTZ_LOCAL_BUILD)
find_package(QtzCore REQUIRED)
find_package(QtzData REQUIRED)
find_package(QtzSecurity REQUIRED)
endif()

# OS-dependent sources
set(OS_SOURCES )
if(WIN32)
    list(APPEND OS_SOURCES QtzWidgets.rc)
endif()

# Define the library
add_library (QtzWidgets SHARED
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
    ${OS_SOURCES})

# Set properties
set_target_properties(QtzWidgets PROPERTIES 
    VERSION 0.4.0
    SOVERSION 0
    DEBUG_POSTFIX d
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED TRUE
    DEFINE_SYMBOL QTZ_WIDGETS_LIBRARY
    PUBLIC_HEADER "include/qtz-widgets.hpp"
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link againsg dependencies
target_link_libraries(QtzWidgets 
    PUBLIC 
        Qt5::Core Qt5::Widgets Qt5::Sql Qt5::Network 
        opencv_core opencv_imgcodecs 
        QtzCore QtzData QtzSecurity
)

# Copy headers for local builds
if(QTZ_LOCAL_BUILD)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND 
    ${CMAKE_COMMAND} -P 
        "${CMAKE_CURRENT_LIST_DIR}/cmake/copy_local_includes.cmake" 
        "${CMAKE_CURRENT_SOURCE_DIR}/include/" "widgets" "${QTZ_LOCAL_INCLUDES_DIR}"
)
endif()

# Install and export

include(GNUInstallDirs)

install(DIRECTORY "include/" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qtz/widgets)

install(TARGETS QtzWidgets
    EXPORT QtzWidgetsConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

export(TARGETS QtzWidgets FILE QtzWidgetsConfig.cmake)

install(EXPORT QtzWidgetsConfig
    FILE QtzWidgetsConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/)


install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtzWidgets.pc 
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

# pkg-config
configure_file(QtzWidgets.pc.in QtzWidgets.pc @ONLY)