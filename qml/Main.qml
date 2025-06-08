import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ChatApp 1.0

ApplicationWindow {
    visible: true
    width: 400; height: 600
    title: "LAN Peer-to-Peer Chat"

    ChatServer { id: server }
    ChatClient { id: client }
    ChatModel  { id: chatModel }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12    // outer margin
        spacing: 8

        RowLayout {
            spacing: 8
            width: parent.width
            TextField { id: host; placeholderText: "Host"; text: "127.0.0.1"; Layout.fillWidth: true }
            TextField { id: port; placeholderText: "Port"; text: "9999"; width: 70 }
            Button   {
                text: "Listen"
                onClicked: server.start(parseInt(port.text))
            }
            Button   {
                text: "Connect"
                onClicked: client.connectToServer(host.text, parseInt(port.text))
            }
        }

        ListView {
            id: view
            Layout.fillWidth: true
            height: 400
            model: chatModel
            delegate: Text {
                wrapMode: Text.Wrap
                text: model.sender + ": " + model.text   // use model roles to avoid binding loop
            }
        }

        RowLayout {
            spacing: 8
            width: parent.width
            TextField {
                id: input
                placeholderText: "Message…"
                Layout.fillWidth: true
                Keys.onReturnPressed: sendButton.clicked()
            }
            Button {
                id: sendButton
                text: "Send"
                onClicked: {
                    if (input.text === "") return;
                    chatModel.appendLine("You", input.text);
                    client.sendMessage(input.text);
                    input.text = "";
                }
            }
        }
    }

    // ----- Signal wiring ---------------------------------

    Connections {
        target: client
        function onConnected()          { chatModel.appendLine("System", "Connected") }
        function onMessageReceived(msg) { chatModel.appendLine("Peer",   msg) }
        function onErrorOccurred(err)   { chatModel.appendLine("System", err) }
    }

    Connections {
        target: server
        function onNewMessage(txt) { chatModel.appendLine("Peer", txt) }
    }
}