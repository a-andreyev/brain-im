import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import BrainIM 0.1
import TelepathyQt 0.1

import "../../components"
import "../accounts"

ScrollablePage {
    id: page

    function create(manager, protocol) {
        mode = mode_create
        console.log("Create acc", manager, protocol)
        accountParameterModel.newAccount(manager, protocol)
    }

    function setAccount(account) {
        mode = mode_update
        console.log("Set account", account)
        accountParameterModel.setAccount(account)
    }

    signal createAccount(string manager, string protocol, string displayName, variant parameters)

    property int mode: mode_create
    readonly property int mode_create: 0
    readonly property int mode_update: 1

    Column {
        id: internalCol
        width: page.width

        Item {
            id: displayNameEditor2
            height: 50
            width: 300
            RowLayout {
                spacing: 4
                Label {
                    text: qsTr("DisplayName")
                    width: 200
                    Layout.preferredWidth: 200
                }
                TextField {
                    id: displayNameEditor
                    width: 200
                    selectByMouse: true
                    text: accountParameterModel.displayName
                    Layout.preferredWidth: 200
                }
            }
        }

        Repeater {
            id: parametersDetailView
            model: accountParameterModel
            readonly property int delegateHeight: 50

            delegate: Item {
                id: delegate
                height: parametersDetailView.delegateHeight
                width: page.width
                RowLayout {
                    spacing: 4
                    Label {
                        text: model.name
                        Layout.preferredWidth: 200
                        height: 40
                    }
                    Loader {
                        id: paramEditor
                        sourceComponent: getComponentForType(model.signature)
                        width: 200
                        height: 48
                        Layout.preferredHeight: 48
                        Layout.preferredWidth: 200
                        Binding {
                            target: paramEditor.item
                            property: "value"
                            value: model.value
                            delayed: true
                        }
                        Binding {
                            target: paramEditor.item
                            property: "secret"
                            value: model.secret
                            delayed: true
                            when: model.secret
                        }

                        function getComponentForType(t)
                        {
                            if (t === "u") {
                                return intDelegate
                            } else if (t === "b") {
                                return boolDelegate
                            } else if (t === "s") {
                                return textDelegate
                            }

                            console.warn("Fallback to text delegate")

                            return textDelegate
                        }
                    }
                }
                Connections {
                    target: paramEditor.item
                    onSubmit: {
                        console.log("Submit param", model.index, value);
                        accountParameterModel.setData(model.index, value)
                    }
                }
            }
        }

        AccountParameterModel {
            id: accountParameterModel
        }

        Component {
            id: intDelegate
            SpinBox {
                signal submit(var value)
                width: 40
                height: 48
                onValueChanged: submit(value)
            }
        }
        Component {
            id: textDelegate
            TextField {
                id: textInnerDelegate
                signal submit(var value)
                property bool secret: false
                property alias value: textInnerDelegate.text
                width: 40
                height: 48
                selectByMouse: true
                onTextChanged: submit(text)
                echoMode: secret ? TextInput.Password : TextInput.Normal
            }
        }
        Component {
            id: boolDelegate
            CheckBox {
                signal submit(var value)
                property var value
                width: 40
                height: 48
                checked: value
                onTextChanged: submit(checked)
            }
        }
    }

    footer: Button {
        id: submitButton
        text: page.mode === page.mode_create ? qsTr("Create account") : qsTr("Save")
        onClicked: {
            console.log(text)
            if (page.mode === page.mode_create) {
                page.createAccount(accountParameterModel.manager, accountParameterModel.protocol, displayNameEditor.text, accountParameterModel.getVariantMap())
            } else {
                accountParameterModel.submit()
            }
        }
    }
}
