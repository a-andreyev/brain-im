import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import BrainIM 0.1
import TelepathyQt 0.1

import "../components"
import "accounts"

AccountView {
    id: page

    footer: Button {
        id: addAccount
        text: "Add account"
        onClicked: {
            stackView.push("accounts/ConnectionManagerView.qml", {
                               "title": text
                           })
        }
    }
}
