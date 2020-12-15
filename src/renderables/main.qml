import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

GridLayout {
  anchors.fill: parent
  columns: 2
  rows: 2

  Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "green"
  }
  Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "blue"
  }
  Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "cyan"
  }
  Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "magenta"
  }
}
