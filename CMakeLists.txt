cmake_minimum_required(VERSION 3.12)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

project(qspeedreader VERSION 0.3.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(version)

add_executable(${PROJECT_NAME}
    src/colordialog.cpp
    src/colordialog.h
    src/colordialog.ui
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/settings.h
    src/settings.cpp
    resources/resources.qrc
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        src
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Widgets
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Auto. CCACHE
if(UNIX)
    find_program(CCACHE_FOUND ccache)

    if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    endif(CCACHE_FOUND)
endif()

# Auto. distcc
if(UNIX)
    find_program(DISTCC_FOUND distcc)

    if(DISTCC_FOUND)
        set(ENV{CCACHE_PREFIX} distcc)
    endif(DISTCC_FOUND)
endif()


if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    install(FILES resources/org.ballessay.qspeedreader.desktop DESTINATION share/applications)
    install(FILES resources/qspeedreader.png DESTINATION share/icons/hicolor/128x128/apps)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


option(USE_ASAN "Build with address sanitizer" OFF)

if(USE_ASAN)
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
endif()
