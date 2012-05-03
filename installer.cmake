# Bundle the executable so that it doesn't require all the dll to be shiped
include(DeployQt4)
install_qt4_executable("." MagicPad)

# CPack configuration for NSIS installer
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR         ${MAGICPAD_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR         ${MAGICPAD_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH         ${MAGICPAD_VERSION_PATCH})
set(CPACK_PACKAGE_EXECUTABLES           "..\\\\MagicPad" "MagicPad")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY   "MagicPad Demonstration Software")
set(CPACK_PACKAGE_ICON                  "${CMAKE_CURRENT_SOURCE_DIR}\\\\isorg.ico")
set(CPACK_PACKAGE_VENDOR                "Isorg, www.isorg.fr")
#set(CPACK_PACKAGE_DESCRIPTION_FILE      "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
#set(CPACK_RESOURCE_FILE_LICENSE         "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
set(CPACK_PACKAGE_INSTALL_DIRECTORY     "ISORG\\\\MagicPad ${MAGICPAD_VERSION_MAJOR}.${DEMO3_VERSION_MINOR}")
# There is a bug in NSI that does not handle full unix paths properly. Make
# sure there is at least one set of four (4) backlasshes.
set(CPACK_NSIS_INSTALLED_ICON_NAME      "MagicPad.exe")
set(CPACK_NSIS_DISPLAY_NAME             "MagicPad ${MAGICPAD_VERSION_MAJOR}.${DEMO3_VERSION_MINOR}")
set(CPACK_NSIS_HELP_LINK                "http:\\\\\\\\www.isorg.fr")
set(CPACK_NSIS_URL_INFO_ABOUT           "http:\\\\\\\\www.isorg.fr")
set(CPACK_NSIS_CONTACT                  "contact@isorg.fr")
#set(CPACK_NSIS_MODIFY_PATH              ON)

include(CPack)