import QtQuick 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.15

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

      Row {
        layoutDirection: Qt.RightToLeft
        spacing: 10

        width: parent.width - 55
        height: 103

      
        Button {
          id: pair_reject_button

          height: 56
          y: parent.height - height

          text: "    CANCEL PAIR    "
          enabled: true
          visible: true

          font.family: "Helvetica Neue"
          font.pointSize: 24
          font.bold: true

          background: Rectangle {
            color: enabled ? "#9496ff" : "#444444"
            radius: parent.height/2
          }

          onClicked: enabled = !enabled
        }

        Button {
          id: pair_confirm_button

          height: 56
          y: parent.height - height

          text: "    START PAIR    "
          enabled: true

          font.family: "Helvetica Neue"
          font.pointSize: 24
          font.bold: true


          background: Rectangle {
            color: enabled ? "#ff9500" : "#444444"
            radius: parent.height / 2
          }

          onClicked: {
            pair_confirm_button.enabled = !pair_confirm_button.enabled
          }
        }

      }
    }
  }
}
