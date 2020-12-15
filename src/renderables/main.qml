import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Rectangle {
  anchors.fill: parent
  color: "black"

  GridLayout {
    columns: 2
    rows: 2

    Image {
      fillMode: Image.PreserveAspectFit 
      width: 300
      source: "lcars_upper_left"
    }
    Image {
      fillMode: Image.PreserveAspectFit 
      width: 300
      source: "lcars_upper_right"
    }
    Image {
      fillMode: Image.PreserveAspectFit 
      width: 300
      source: "lcars_lower_left"
    }
    Image {
      fillMode: Image.PreserveAspectFit 
      width: 300
      source: "lcars_lower_right"
    }
  }
}
