import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import BrainIM 0.1

Frame {
    id: messageView
    width: 800
    height: 600
    property alias peer: messagesModel.peer

//    ListModel {
//        id: messageModel
//        Component.onCompleted: {
//            append({
//                       type: MessageModel.MessageTypeNewDay,
//                       text: "January 14",
//                   })
//            append({
//                       type: MessageModel.MessageTypeText,
//                       sender: "Andy Hall",
//                       senderPeer: Brain.peerFromContactId(3),
//                       message: "Well, I don't know about that.",
//                       time: "3:57 PM",
//                       messageFlags: 1, // Telegram.Namespace.MessageFlagRead
//                   })
//            append({
//                       type: MessageModel.MessageTypeServiceAction,
//                       sender: "Andy Hall",
//                       users: "Daniel Ash",
//                       time: "4:33 PM",
//                   })
//            append({
//                       type: MessageModel.MessageTypeText,
//                       sender: "Daniel Ash",
//                       senderPeer: Brain.peerFromContactId(2),
//                       message: "It's a joke we were joking around, you see? We totally got you!",
//                       time: "4:34 PM",
//                       messageFlags: 1, // Telegram.Namespace.MessageFlagRead
//                   })
//            append({
//                       type: MessageModel.MessageTypeNewDay,
//                       text: "January 16",
//                   })
//            append({
//                       sender: "You",
//                       senderPeer: Brain.peerFromContactId(1),
//                       message: "We work hard, we play hard",
//                       time: "2:27 PM",
//                       messageFlags: 3,//Telegram.Namespace.MessageFlagOut|Telegram.Namespace.MessageFlagRead
//                   })
//            console.log("Model Completed")
//        }
//    }
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
            model: modelData
        }
    }

    Component {
        id: newDayDelegate
        ServiceMessageDelegate {
            text: Qt.formatDate(modelData.timestamp, Qt.DefaultLocaleLongDate)
        }
    }
    Component {
        id: serviceActionDelegate
        ServiceMessageDelegate {
            text: formatActionText(modelData)
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

    MessagesModel {
        id: messagesModel
    }

    ListView {
        id: listView
        anchors.fill: parent
        model: messagesModel

//        property var modelDataList: []

        delegate: Loader {
            id: messageLoader
//            property var nextData: (listView.count > myIndex + 1) ? listView.contentItem.children[myIndex].modelData : undefined
//            property var prevData: (myIndex - 1 > 0) ? listView.contentItem.children[myIndex].modelData : undefined
            //property var nextData: listView.modelDataList[myIndex+1]
            //property var prevData: listView.itemAt(0, 10).modelData//listView.contentItem.children[myIndex].modelData

            readonly property var modelData: model

            //readonly property int myIndex: index

            //onMyIndexChanged: console.log("My index is " + myIndex +" and data: " + nextData)

//            Binding {
//                target: messageLoader
//                property: "nextData"
////                value: (listView.count > myIndex + 1) ? listView.contentItem.children[myIndex + 1].modelData : undefined
//                value: listView.contentItem.children[messageLoader.myIndex + 1]
//                onValueChanged: {
//                    console.log("Value: " + messageLoader.myIndex + " " + listView.contentItem.children[myIndex])
//                }
//            }

//            Binding {
//                target: messageLoader
//                property: "prevData"
//                value: (myIndex - 1 > 0) ? listView.contentItem.children[myIndex - 1].modelData : undefined
//            }

            width: listView.width - listView.leftMargin - listView.rightMargin
            sourceComponent: {
                switch (modelData.entityType) {
                case Event.NewDay:
                    return newDayDelegate
                case Event.ServiceAction:
                    return serviceActionDelegate
                default:
                    return messageDelegate
                }
            }
        }
    }
}
