import QtQuick 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.15

Rectangle {
  id: "ui"

  width: 1
  height: 1
  color: "black"

  signal initPairing()

  property string myState: "INTERFACE IDLE"

  function showFlickable() {
    controlsGrid.enabled = false
    controlsGrid.visible = false
    flickableImage.enabled = true
    flickableImage.visible = true

    flickableTimer.start()
  }


  function startPairing() {
    ui.initPairing()
  }

  function showGrid() {
    controlsGrid.enabled = true
    controlsGrid.visible = true
    flickableImage.enabled = false
    flickableImage.visible = false
  }
  
  function setReadyState() {
    myState = "INTERFACE READY"
  }

  Timer {
    id: "flickableTimer"

    interval: 3000

    onTriggered: showGrid()
  }

  Timer {
    id: "stateTimer"

    interval: 5000
    running: true

    onTriggered: setReadyState()
  }

  focus: true

  Keys.onEnterPressed: showFlickable()
  Keys.onLeftPressed: showFlickable()
  Keys.onRightPressed: showGrid()

  Flickable {
    id: "flickableImage"

    anchors.fill: parent
    anchors.centerIn: parent

    contentWidth: targetImage.sourceSize.width * targetImage.scale
    contentHeight: targetImage.sourceSize.height * targetImage.scale

    visible: false
    enabled: false

    Image {
      id: "targetImage"
      scale: 10

      anchors.centerIn: parent

      source: "test"
    }
  }

  GridLayout {
    id: "controlsGrid"

    columns: 2
    rows: 2

    Image {
      fillMode: Image.PreserveAspectCrop
      source: "lcars_upper_left"
    }
    Image {
      fillMode: Image.PreserveAspectCrop
      source: "lcars_upper_right"


      Column {
        spacing: 10

        width: parent.width - 41
        anchors.top: parent.top
        anchors.topMargin: 60

        Label {
          height: 90

          horizontalAlignment: Text.AlignRight
          anchors.right: parent.right

          font.family: "Helvetica Neue"
          font.pointSize: 56
          font.bold: true
          color: "#ff9500"

          text: ui.myState
        }

        Button {
          id: pairConfirmButton

          anchors.right: parent.right

          height: 56

          text: "    START PAIR    "
          enabled: true

          font.family: "Helvetica Neue"
          font.pointSize: 24
          font.bold: true


          background: Rectangle {
            color: enabled ? "#ff9500" : "#444444"
            radius: parent.height / 2
          }

          onClicked: startPairing()
        }
      
        Button {
          id: pairRejectButton

          anchors.right: parent.right

          height: 56

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
      }
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
