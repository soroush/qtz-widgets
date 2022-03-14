include(CMakeFindDependencyMacro)
find_package(Qt5 COMPONENTS Core Widgets Sql Network REQUIRED)
find_package(OpenCV CONFIG REQUIRED)
find_package(QtzCore REQUIRED)
find_package(QtzData REQUIRED)
find_package(QtzSecurity REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/QtzWidgetsTargets.cmake")