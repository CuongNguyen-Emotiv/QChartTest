import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Emotiv.QcViewController 1.0
import Emotiv.Constant 1.0

Window {
    id: window
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("Hello World")

    readonly property int chartHeight: width/2

    Column {
        width: parent.width
        height: parent.height
        Row {
            Text {
                id: textPointsPerSec
                text: qsTr("Points per sec: ")
                padding: 10
            }

            ComboBox {
                id: comboboxPointsPerSec
                model: [Constant.lowPointsPerSec(), Constant.highPointsPerSec()]
                currentIndex: 1
                anchors.verticalCenter: textPointsPerSec.verticalCenter
                width: window.width/2
            }
        }

        Row {
            Text {
                id: textChartNumber
                text: qsTr("Chart number: ")
                padding: 10
            }

            ComboBox {
                id: comboboxChartNumber
                model: Constant.maxChartNumber()
                anchors.verticalCenter: textChartNumber.verticalCenter
                width: window.width/2
            }
        }

        Row {
            Text {
                id: textChartType
                text: qsTr("Chart type: ")
                padding: 10
            }

            ComboBox {
                id: comboboxChartType
                model: [Constant.qtChartView(), Constant.qwtView()]
                anchors.verticalCenter: textChartType.verticalCenter
                width: window.width/2
            }
        }

        Row {
            Button {
                id: startButton
                text: "Start"
                width: window.width/2
            }
            Button {
                id: stopButton
                text: "Stop"
                width: window.width/2
            }
        }

        Text {
            text: "FPS: " + fpsmonitor.freq
        }

        Loader {
            id: chartViewLoader
            width: parent.width
            height: {
                var tempHeight = 0
                for (var i = 0; i < parent.children.length - 1; i++) {
                    tempHeight += parent.children[i].height
                }
                return parent.height - tempHeight
            }
            clip: true
            source: {
                if (comboboxChartType.currentText === Constant.qtChartView()) {
                    return "qrc:/QtChartView.qml"
                } else {
                    return "qrc:/QwtView.qml"
                }
            }
        }
    }
}
