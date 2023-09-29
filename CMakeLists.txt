cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME ChartTest)

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
    Core
    Quick
    Charts
    Widgets
    Concurrent
    Gui
    PrintSupport
    Svg
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Quick
    Charts
    Widgets
    Concurrent
    Gui
    PrintSupport
    Svg
)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        Constant.h Constant.cpp
        Controller.h Controller.cpp
        DataProducer.h DataProducer.cpp
        Singleton.h

        QChart/QcController.h QChart/QcController.cpp
        QChart/QcDataProducer.h QChart/QcDataProducer.cpp

        Qwt/QwtChart.h Qwt/QwtChart.cpp
        Qwt/QwtController.h Qwt/QwtController.cpp
        Qwt/QwtDataProducer.h Qwt/QwtDataProducer.cpp

        Pro/QuickQwtPlot.h Pro/QuickQwtPlot.cpp
        Pro/QuickCurve.h Pro/QuickCurve.cpp
        Pro/ProDataProceducer.h Pro/ProDataProceducer.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
          ${PROJECT_SOURCES}
        )
    endif()
endif()


include(${CMAKE_CURRENT_SOURCE_DIR}/lqtutils/CMakeLists.txt)

set(LIBS
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Concurrent
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::PrintSupport
    Qt${QT_VERSION_MAJOR}::Svg
    lqtutils)

message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    if(${CMAKE_OSX_ARCHITECTURES} MATCHES "x86_64")
        message(FATAL_ERROR "Please add qwt lib for macos x86_64 architecture here")
    else()
        set(LIBS ${LIBS} ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/qwt/macos_arm64/lib/libqwt.a)
        target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/qwt/macos_arm64/include)
    endif()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "iOS")
    set(LIBS ${LIBS} ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/qwt/ios_arm64/lib/libqwt.a)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/qwt/ios_arm64/include)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Android")
    message("CMAKE_ANDROID_ARCH_ABI: " ${CMAKE_ANDROID_ARCH_ABI})
    if (${CMAKE_ANDROID_ARCH_ABI} MATCHES "arm64-v8a")
        set(LIBS ${LIBS} ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/qwt/android_arm64_v8a/lib/libqwt_arm64-v8a.a)
        target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/qwt/android_arm64_v8a/include)
    else()
        message(FATAL_ERROR "Please add qwt lib for this compiler")
    endif()
else()
    message(FATAL_ERROR "Please add qwt lib for this compiler")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/QChart)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Qwt)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Pro)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  ${LIBS}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${PROJECT_NAME})
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(${PROJECT_NAME})
    qt_finalize_executable(${PROJECT_NAME})
endif()
