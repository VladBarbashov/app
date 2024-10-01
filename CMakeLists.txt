cmake_minimum_required(VERSION 3.16)

project(app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED)

pkg_check_modules(LIBPQXX REQUIRED libpqxx)
pkg_check_modules(LIBPQ REQUIRED libpq)

include_directories(libs auth database monitor ${LIBPQXX_INCLUDE_DIRS} ${LIBPQ_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})

set(PROJECT_HEADERS
    libs/json.h

    database/dbvalidator.h

    auth/authexceptions.h
    auth/usercontroller.h
    auth/loginwindow.h
    auth/registerwindow.h

    monitor/tempreader.h
    monitor/mainwindow.h
)

set(PROJECT_SOURCES
    main.cpp

    database/dbvalidator.cpp

    auth/usercontroller.cpp
    auth/loginwindow.cpp
    auth/registerwindow.cpp

    monitor/tempreader.cpp
    monitor/mainwindow.cpp
)

set(PROJECT_UIS
    auth/loginwindow.ui
    auth/registerwindow.ui

    monitor/mainwindow.ui
)

set(PROJECT_FILES
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
    ${PROJECT_UIS}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(app
        MANUAL_FINALIZATION
        ${PROJECT_FILES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET app APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(app SHARED
            ${PROJECT_FILES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(app
            ${PROJECT_FILES}
            auth/authvalidator.h
            auth/passwdvalidator.h auth/passwdvalidator.cpp
            auth/loginvalidator.h auth/loginvalidator.cpp
            database/tablevalidator.h
            database/usertablevalidator.h database/usertablevalidator.cpp
        )
    endif()
endif()

target_link_libraries(app
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE ${LIBPQXX_LIBRARIES}
    PRIVATE ${LIBPQ_LIBRARIES}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.app)
endif()
set_target_properties(app PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(app)
endif()
