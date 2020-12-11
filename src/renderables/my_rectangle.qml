import QtQuick

Item {
  id: container
  Rectangle {
    color: "green"
    width: container.width
    height: container.height

    Rectangle {
      width: 80; height: 80
      anchors.centerIn: parent
      color: "red"
    }
  }
}
  

