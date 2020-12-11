import QtQuick
import QtQuick.Controls
import "qrc:/custom"

ApplicationWindow
{
  visible: true
  width: 640
  height: 480
  title: qsTr("Minimal Qml")

  Red {
    anchors.left: parent.left
  }
  Blue {
    anchors.right: parent.right
  }
}
