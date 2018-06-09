import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import BrainIM 0.1

Frame {
    id: messageView
    width: 800
    height: 600
    property alias peer: messageModel2.peer

    ListModel {
        id: messageModel
        Component.onCompleted: {
            append({
                       type: MessageModel.MessageTypeNewDay,
                       text: "January 14",
                   })
            append({
                       type: MessageModel.MessageTypeText,
                       sender: "Andy Hall",
                       senderPeer: Brain.peerFromContactId(3),
                       message: "Well, I don't know about that.",
                       time: "3:57 PM",
                       messageFlags: 1, // Telegram.Namespace.MessageFlagRead
                   })
            append({
                       type: MessageModel.MessageTypeServiceAction,
                       sender: "Andy Hall",
                       users: "Daniel Ash",
                       time: "4:33 PM",
                   })
            append({
                       type: MessageModel.MessageTypeText,
                       sender: "Daniel Ash",
                       senderPeer: Brain.peerFromContactId(2),
                       message: "It's a joke we were joking around, you see? We totally got you!",
                       time: "4:34 PM",
                       messageFlags: 1, // Telegram.Namespace.MessageFlagRead
                   })
            append({
                       type: MessageModel.MessageTypeNewDay,
                       text: "January 16",
                   })
            append({
                       sender: "You",
                       senderPeer: Brain.peerFromContactId(1),
                       message: "We work hard, we play hard",
                       time: "2:27 PM",
                       messageFlags: 3,//Telegram.Namespace.MessageFlagOut|Telegram.Namespace.MessageFlagRead
                   })
            console.log("Model Completed")
        }
    }
    Connections {
        target: messageSendStubProxy
        onMessageSent: {
            var text = message
            var dateTime = new Date()
            var timeText = Qt.formatTime(dateTime, "h:mm AP")
            timeText = timeText.slice(0, -3)
            if (dateTime.getHours() >= 12) {
                timeText += " PM"
            } else {
                timeText += " AM"
            }

            messageModel.append({
                                    type: MessageModel.MessageTypeText,
                                    sender: "You",
                                    senderPeer: Brain.peerFromContactId(1),
                                    message: text,
                                    time: timeText
                                })
        }
    }

    Component {
        id: messageDelegate
        MessageDelegate {
        }
    }

    Component {
        id: newDayDelegate
        ServiceMessageDelegate {
            text: modelData.text
        }
    }
    Component {
        id: serviceActionDelegate
        ServiceMessageDelegate {
            text: mkLinkToPeer(modelData.sender) + " added " + mkLinkToPeer(modelData.users)
            plainText: modelData.sender + " added " + modelData.users
            textFormat: Text.StyledText
            linkColor: textColor
            function mkLinkToPeer(peer) {
                return "<a href=\"" + peer + "\">" + peer + "</a>"
            }
            onLinkActivated: {
                console.log("Link activated: " + link)
            }
        }
    }

    MessageModel {
        id: messageModel2
    }

    ListView {
        id: listView
        anchors.fill: parent
        model: messageModel
        delegate: Loader {
            readonly property var modelData: listView.model.get(index)
            width: listView.width - listView.leftMargin - listView.rightMargin
            sourceComponent: {
                switch (modelData.type) {
                case MessageModel.MessageTypeNewDay:
                    return newDayDelegate
                case MessageModel.MessageTypeServiceAction:
                    return serviceActionDelegate
                default:
                    return messageDelegate
                }
            }
        }
    }
}
