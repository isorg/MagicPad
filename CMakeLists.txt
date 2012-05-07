# ======================================================
# MagicPad
# ======================================================
cmake_minimum_required(VERSION 2.8.7)

# Project name
project(MAGICPAD)

#list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/Modules")

# include cmake scripts
include(CMake/magicpad-macros.cmake)
include(CMake/magicpad-testing.cmake)
include(CMake/magicpad-version.cmake)
#message(STATUS ${MAGICPAD_VERSION_STR})

#
# DLLs'
#
magicpad_install_files(3rdparty/dll/libgcc_s_dw2-1.dll ".")
magicpad_install_files(3rdparty/dll//libstdc++-6.dll ".")
magicpad_install_files(3rdparty/dll//mingwm10.dll ".")

#
# Find QT
#
find_package(Qt4 REQUIRED)
set(QT_USE_QTOPENGL TRUE)
set(QT_USE_QTXML TRUE)
set(QT_USE_QTWEBKIT TRUE)
set(QT_USE_PHONON TRUE)

include(${QT_USE_FILE})

set(CMAKE_AUTOMOC TRUE)

set(QtApp_RCCS resources.qrc)
qt4_add_resources(QtApp_RCC_SRCS ${QtApp_RCCS})

get_filename_component(QT_DLL_PATH ${QT_QMAKE_EXECUTABLE} PATH)
magicpad_install_files(${QT_DLL_PATH}/QtCore4.dll ".")
magicpad_install_files(${QT_DLL_PATH}/QtGui4.dll ".")
magicpad_install_files(${QT_DLL_PATH}/QtOpenGL4.dll ".")
magicpad_install_files(${QT_DLL_PATH}/QtXml4.dll ".")
magicpad_install_files(${QT_DLL_PATH}/QtWebkit4.dll ".")
magicpad_install_files(${QT_DLL_PATH}/QtNetwork4.dll ".")
magicpad_install_files(${QT_DLL_PATH}/../plugins/imageformats/qjpeg4.dll "imageformats/.")
magicpad_install_files(${QT_DLL_PATH}/phonon4.dll ".")
magicpad_install_files(${QT_DLL_PATH}/../plugins/phonon_backend/phonon_ds94.dll "phonon_backend/.")

#
# Find FTDI library
#
include_directories("${PROJECT_SOURCE_DIR}/3rdparty/ftdi")
link_directories("${PROJECT_SOURCE_DIR}/3rdparty/ftdi/i386")
magicpad_install_files("${PROJECT_SOURCE_DIR}/3rdparty/ftdi/i386/ftd2xx.dll" ".")

#
# QsLog library
#
include_directories("3rdparty/QsLog")
add_subdirectory("3rdparty/QsLog")

#
# Find OpenCV
#
find_package(OpenCV REQUIRED)

#
# QWT 3D Plot
#
include_directories("${PROJECT_SOURCE_DIR}/3rdparty/qwt3d/include")
link_directories("${PROJECT_SOURCE_DIR}/3rdparty/qwt3d/lib")
magicpad_install_files("${PROJECT_SOURCE_DIR}/3rdparty/qwt3d/lib/qwtplot3d.dll" ".")

#
# Plugins
#
magicpad_install_files("${PROJECT_SOURCE_DIR}/data/.placeholder" "plugins/.")
set(PLUGIN_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/plugins")

add_subdirectory(src)
include_directories(src)

add_executable(MagicPad WIN32
    ${MAGICPAD_SRCS}
    ${QSLOG_SRCS}
    ${ENUMSER_SRCS}
    ${QtApp_RCC_SRCS}    
    icon.rc
    )

# TODO: fix application manifest
#set_target_properties(MagicPad PROPERTIES LINK_FLAGS "-D/MANIFESTUAC:level='requireAdministrator'")

target_link_libraries(MagicPad
    ${QT_LIBRARIES}
    qwtplot3d
    ${OpenCV_LIBS}
    ftd2xx
    )

install(TARGETS MagicPad DESTINATION ".")

#
# Copy files
#
magicpad_install_files("config.ini" ".")

#
# Install all files in the 'data' subdirectory
#
file(GLOB_RECURSE DATA_FILES "data/*")
foreach(dfile ${DATA_FILES})
    file(RELATIVE_PATH  drpath "${PROJECT_SOURCE_DIR}" ${dfile})
    get_filename_component(subpath ${drpath} PATH)
    magicpad_install_files(${dfile} "${subpath}/.")
endforeach()

magicpad_install_files("Presentation ISORG.pdf"  ".")

#
# Copy drivers
#
file(GLOB_RECURSE DRIVER_FILES "drivers/*")
foreach(dfile ${DRIVER_FILES})
    file(RELATIVE_PATH  drpath "${PROJECT_SOURCE_DIR}" ${dfile})
    get_filename_component(subpath ${drpath} PATH)
    magicpad_install_files(${dfile} "${subpath}/.")
endforeach()

#
# Documentation
#
#add_subdirectory(doc)

#
# Installer
#
include(CMake/magicpad-installer.cmake)