import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import BrainIM 0.1
import BrainIM.Telepathy 0.1

import "dialogs"
import "messages"

Page {
    id: mainScreen

    property alias peer: messagesModel.peer

    function showDialog(peer)
    {
        console.log("Show dialog with peer(" + peer.type + ", " + peer.id + ")")
        peer = Brain.peer(peer.id, peer.type)
    }

    Row {
        id: contentRoot
        anchors.fill: mainScreen.contentItem
        DialogView {
            id: dialogView
            width: 360
            height: parent.height
            model: contactsModel
            onActivateDialog: mainScreen.showDialog(peer)
        }

        Item {
            id: rightColumn
            visible: width > 200
            width: parent.width - dialogView.width
            height: parent.height

            MessageToolbar {
                id: chatToolbar
                anchors.top: parent.top
                width: rightColumn.width
                height: 48
                z: 1
            }
            MessageView {
                id: messageView
                width: rightColumn.width
                anchors.top: chatToolbar.bottom
                anchors.bottom: messageEditor.top
                model: messagesModel
                onActivateDialog: mainScreen.showDialog(peer)
            }
            MessageEditor {
                id: messageEditor
                peer: mainScreen.peer
                width: rightColumn.width
                height: 64
                anchors.bottom: rightColumn.bottom
            }
        }
    }

    QtObject {
        id: messageSendStubProxy
        signal messageSent(string message, var peer)
        onMessageSent: {
            var typeText = (peer.type === Peer.Contact ? "User" : "Chat")
            console.log("Message to " + typeText + " " + peer.id)
        }
        signal draftChanged(string message, var peer)
    }


    ContactsModel {
        id: contactsModel
    }

    TelepathyMessagesModel {
        id: messagesModel
    }
}
