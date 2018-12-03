project(QmlClient)

find_package(Qt5 REQUIRED COMPONENTS Core Network DBus Xml Gui Qml Quick)

if (USE_TELEPATHY)
    add_definitions(-DUSE_TELEPATHY)
endif()

set(brain_qml_SOURCES
    main.qml
    pages/AccountManagement.qml
    pages/IndexPage.qml
    pages/MainView.qml
)

add_executable(brain_im main.cpp ${brain_qml_SOURCES})

set_target_properties(brain_im PROPERTIES AUTOMOC TRUE)

target_include_directories(brain_im PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/brain-im

    ${TELEPATHY_QT_INCLUDE_DIR}
)

target_link_libraries(brain_im
    Qt5::Core
    Qt5::Gui
    Qt5::Network
    Qt5::Qml
    Qt5::Quick
    BrainIM

    ${TELEPATHY_QT_LIBRARIES}
)

if (NOT INSTALL_QML_IMPORT_DIR)
    set(INSTALL_QML_IMPORT_DIR ${CMAKE_INSTALL_LIBDIR}/qt5/qml)
endif()

set(QML_IMPORT_PATH ${INSTALL_QML_IMPORT_DIR})

install(
    FILES ${brain_qml_SOURCES}
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/brain-im/qml
)
