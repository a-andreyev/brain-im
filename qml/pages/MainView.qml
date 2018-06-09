import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import BrainIM 0.1

import "dialogs"
import "messages"

Page {
    id: mainScreen
    Row {
        id: contentRoot
        anchors.fill: mainScreen.contentItem
        DialogView {
            id: dialogView
            width: 400
            height: parent.height
            onActivateDialog: {
                console.log("Activate dialog peer(" + peer.type + ", " + peer.id + ")")
                messageView.peer = Brain.makePeer(peer.id, peer.type)
            }
        }

        Item {
            id: rightColumn
            visible: width > 200
            width: parent.width - dialogView.width
            height: parent.height
            MessageView {
                id: messageView
                peer: Brain.peerFromRoomId(1)
                width: rightColumn.width
                anchors.top: rightColumn.top
                anchors.bottom: messageEditor.top
            }
            MessageEditor {
                id: messageEditor
                peer: messageView.peer
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
            var typeText = (peer.type == 0 ? "User" : "Chat")
            console.log("Message to " + typeText + " " + peer.id)
        }
        signal draftChanged(string message, var peer)
    }
}
