import QtQuick.Layouts
import QtQuick
import QtQuick.Controls



RowLayout {
  id: layout
  spacing: 6
  
  Rectangle {
    color: 'gray'
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.preferredWidth: 64
    Layout.maximumWidth: 64
    Layout.minimumWidth: 64
  }

  Rectangle {
    color: "teal"
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.minimumWidth: 200
    Layout.preferredWidth: 250
    Layout.maximumWidth: 300
    ListView {
      anchors.fill: parent
      model: api_results
      rebound: Transition {
        NumberAnimation {
          properties: "y"
          duration: 400
          easing.type: Easing.OutQuart
        }
      }
      delegate: Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        height: 75
        Text {
          anchors.horizontalCenter: parent.horizontalCenter
          anchors.top: parent.top
          text: name
        }
        Text {
          anchors.horizontalCenter: parent.horizontalCenter
          anchors.bottom: parent.bottom
          text: email
        }
      }
    }
  }
  

  ListModel {
    id: api_results
    ListElement { name: "My Self"; email: "some@some.com" }
    ListElement { name: "Schlomo Vaknin"; email: "some@schlomo.com" }
    ListElement { name: "Venus Sanchez"; email: "zak@schlomo.com" }
    ListElement { name: "Beboe Nomergetzen"; email: "bb@zz.com" }
    ListElement { name: "My Self"; email: "some@some.com" }
    ListElement { name: "Schlomo Vaknin"; email: "some@schlomo.com" }
    ListElement { name: "Venus Sanchez"; email: "zak@schlomo.com" }
    ListElement { name: "Beboe Nomergetzen"; email: "bb@zz.com" }
    ListElement { name: "My Self"; email: "some@some.com" }
    ListElement { name: "Schlomo Vaknin"; email: "some@schlomo.com" }
    ListElement { name: "Venus Sanchez"; email: "zak@schlomo.com" }
    ListElement { name: "Beboe Nomergetzen"; email: "bb@zz.com" }
    ListElement { name: "My Self"; email: "some@some.com" }
    ListElement { name: "Schlomo Vaknin"; email: "some@schlomo.com" }
    ListElement { name: "Venus Sanchez"; email: "zak@schlomo.com" }
    ListElement { name: "Beboe Nomergetzen"; email: "bb@zz.com" }
    ListElement { name: "My Self"; email: "some@some.com" }
    ListElement { name: "Schlomo Vaknin"; email: "some@schlomo.com" }
    ListElement { name: "Venus Sanchez"; email: "zak@schlomo.com" }
    ListElement { name: "Beboe Nomergetzen"; email: "bb@zz.com" }
  }


  Rectangle {
    color: 'plum'
    Layout.fillWidth: true
    Layout.fillHeight: true
    TextArea {
      anchors.fill: parent
      anchors.margins: 30
      text: "TextArea\n...\n...\n...\n...\n...\n...\n"
      Rectangle {
        color: "orange"
        width: 100
        height: 100
      }
    }
  }
}
