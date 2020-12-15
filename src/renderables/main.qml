import QtQuick 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

Rectangle {
  width: 1
  height: 1
  color: "black"

  GridLayout {
    columns: 2
    rows: 2

    Image {
      fillMode: Image.PreserveAspectCrop
      source: "lcars_upper_left"
    }
    Image {
      fillMode: Image.PreserveAspectCrop
      source: "lcars_upper_right"
    }
    Image {
      fillMode: Image.PreserveAspectCrop
      source: "lcars_lower_left"
    }
    Image {
      fillMode: Image.PreserveAspectCrop
      source: "lcars_lower_right"
    }
  }
}
