import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import BrainIM 0.1

ScrollablePage {
    id: page

    Column {
        width: parent.width
        Repeater {
            model: 5 //ConnectionManagersModel { }
            delegate: ItemDelegate {
                id: managerDelegate
                text: "Name: " + index //model.name
                width: page.width
                height: 10
//                onClicked: {
//                    stackView.push("ProtocolView.qml", {
//                                       "title": model.name,
//                                       "managers": model.name
//                                   })
//                }
            }
        }
    }
}
