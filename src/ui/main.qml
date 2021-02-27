import QtQuick 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.15

Rectangle {
  id: "ui"

  width: 1
  height: 1
  color: "black"

  signal pleaseOpenConnection()
  signal pleaseCloseConnection()

  property string myState: "NANOKIOSK IDLE"
  property int aspectWidth: 3
  property int aspectHeight: 4

  // UI mutation

  function showFlickable() {
    console.log("Showing the image!")
    controlsGrid.enabled = false
    controlsGrid.visible = false
    flickableImage.enabled = true
    flickableImage.visible = true
  }

  function showGrid() {
    controlsGrid.enabled = true
    controlsGrid.visible = true
    flickableImage.enabled = false
    flickableImage.visible = false
  }

  function loadImage(url) {
    targetImage.source = url
    showFlickable()
    console.log("Source size is", targetImage.sourceSize)
  }

  function setImageScale() {
    const targetAspect = aspectWidth / aspectHeight
    const imageSize = targetImage.sourceSize

    const lengthRatio = imageSize.width / flickableImage.width
    const heightRatio = imageSize.height / flickableImage.height

    const ratioCalcValue = lengthRatio > heightRatio ? lengthRatio : heightRatio

    targetImage.scale = 1.0 / ratioCalcValue
  }

  // State transitions

  function toPairing() {
    ui.pleaseOpenConnection()
    pairConfirmButton.enabled = false
    myState = "AWAITING CONNECTION"
  }

  function toIdle() {
    myState = "NANOKIOSK IDLE"
    pairConfirmButton.enabled = true
    showGrid()
  }

  function toConnected() {
    myState = "CLIENT CONNECTED"

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
      scale: 1

      anchors.centerIn: parent

      source: "test"

      onStatusChanged: {
        if (status == Image.Ready) {
          setImageScale()
        }
      }
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

          onClicked: toPairing()
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

          onClicked: ui.pleaseCloseConnection()
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
