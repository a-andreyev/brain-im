import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import BrainIM 0.1

ScrollablePage {
    id: page

    Component {
        id: addAccountComponent
        ConnectionManagerView {
        }
    }

    footer: Button {
        id: addAccount
        text: "Add account"
        onClicked: {
            stackView.push(addAccountComponent, { "title": text })
        }
    }
}
