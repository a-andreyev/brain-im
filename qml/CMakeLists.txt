project(QmlClient)

#find_package(Qt5 REQUIRED COMPONENTS Core Network DBus Xml Gui Qml Quick)

if (USE_TELEPATHY)
    add_definitions(-DUSE_TELEPATHY)
endif()

set(brain_qml_SOURCES
    main.cpp
    main.qml
    components/ScrollablePage.qml
    pages/AccountManagement.qml
    pages/IndexPage.qml
    pages/MainView.qml
    pages/accounts/AccountEditor.qml
    pages/accounts/AccountView.qml
    pages/accounts/ConnectionManagerView.qml
    pages/accounts/ProtocolView.qml
    pages/dialogs/DialogDelegate.qml
    pages/dialogs/DialogView.qml
    pages/messages/MessageDelegate.qml
    pages/messages/MessageEditor.qml
    pages/messages/MessageView.qml
    pages/messages/ServiceMessageDelegate.qml
)

add_executable(brain_im ${brain_qml_SOURCES})

set_target_properties(brain_im PROPERTIES AUTOMOC TRUE)

target_include_directories(brain_im PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../base

    ${QT5_INCLUDES}
    ${TELEPATHY_QT5_INCLUDE_DIR}
)

target_link_libraries(brain_im
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Widgets
    Qt5::Quick
    Qt5::DBus
    ${TELEPATHY_QT5_LIBRARIES}
    BrainIM
)
