import QtQuick 2.9
import QtQuick.Controls 2.2
import BrainIM 0.1

ItemDelegate {
    id: messageDelegate
    height: details.height
    property int margin: (pictureFrame.width - picture.width) / 2
    Item {
        id: pictureFrame
        height: 64
        width: height
        Rectangle {
            id: picture
            color: "black"
            width: 48
            height: 48
            anchors.centerIn: pictureFrame
        }
    }
    Item {
        id: details
        height: {
            var contentHeight = nameLabel.height + messageLabel.implicitHeight
            if (contentHeight > pictureFrame.height) {
                return contentHeight
            }
            return pictureFrame.height
        }
        anchors.left: pictureFrame.right
        anchors.right: messageDelegate.right
        anchors.rightMargin: messageDelegate.margin

        Label {
            id: nameLabel
            text: modelData.sender
            //font.pixelSize: Theme.fontSizeSmall
        }
        Label {
            id: messageLabel
            anchors.top: nameLabel.bottom
            anchors.left: details.left
            anchors.right: details.right
            text: modelData.message
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            //font.pixelSize: Theme.fontSizeTiny
        }
        Label {
            id: deliveryStatus
            anchors.bottom: details.bottom
            anchors.right: details.right
            readonly property string time: modelData.time
            text: {
                //if (model.messageFlags & Telegram.Namespace.MessageFlagOut) {
                //    if (model.messageFlags & Telegram.Namespace.MessageFlagRead) {
                //        return "\u2713\u2713 " + time // "\u2714"?
                //    }
                //    return "\u2713 " + time
                //}
                return time
            }
            //font.pixelSize: Theme.fontSizeTiny - 4
        }
    }

    Component.onCompleted: {
        console.log("Status:" + modelData + "|" + modelData.message)
    }
}
