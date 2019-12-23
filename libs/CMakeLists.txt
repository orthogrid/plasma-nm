add_definitions(-DTRANSLATION_DOMAIN=\"plasmanetworkmanagement-libs\")

set(plasmanm_internal_SRCS
    models/appletproxymodel.cpp
    models/editoridentitymodel.cpp
    models/editorproxymodel.cpp
    models/networkitemslist.cpp
    models/networkmodel.cpp
    models/networkmodelitem.cpp

    debug.cpp
    handler.cpp
    uiutils.cpp
)

add_library(plasmanm_internal SHARED ${plasmanm_internal_SRCS})

target_link_libraries(plasmanm_internal
    plasmanm_editor
    KF5::NetworkManagerQt
    KF5::Solid
    KF5::Completion
    KF5::I18n
    KF5::IconThemes
    KF5::Plasma
    KF5::Notifications
    Qt5::Xml
    Qt5::Network
)

target_include_directories(plasmanm_internal INTERFACE
  $<INSTALL_INTERFACE:include/plasma-nm>
)

if (WITH_MODEMMANAGER_SUPPORT)
    target_link_libraries(plasmanm_internal KF5::ModemManagerQt)
endif()

install(TARGETS plasmanm_internal
    EXPORT plasmanmConfig
    ${INSTALL_TARGETS_DEFAULT_ARGS}
)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/" # source directory
    DESTINATION "include/plasma-nm" # target directory
    FILES_MATCHING # install only matched files
    PATTERN "*.h" # select header files
)

export(EXPORT plasmanmConfig FILE plasmanmConfig.cmake)
install(EXPORT plasmanmConfig
    DESTINATION share/plasmanmConfig/cmake
)

add_subdirectory(declarative)
add_subdirectory(editor)
