import QtQuick
import QtQuick.Window
import QtCharts 2.5
import Emotiv.ChartViewController 1.0
import QtQuick.Controls

Window {
    id: window
    objectName: "cuongkjm"
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
                model: [128, 256]
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
                model: 65
                anchors.verticalCenter: textChartNumber.verticalCenter
                width: window.width/2
            }
        }

        Row {
            Button {
                text: "Start"
                onClicked: {
                    chartView.removeAllSeries();
                    ChartViewController.setPointsPerSec(comboboxPointsPerSec.textAt(comboboxPointsPerSec.currentIndex))
                    ChartViewController.createSeries(chartView, comboboxChartNumber.currentIndex)
                }
                width: window.width/2
            }
            Button {
                text: "Stop"
                onClicked: {
                    ChartViewController.stopDataProducer()
                }
                width: window.width/2
            }
        }

        Text {
            text: "FPS: " + fpsmonitor.freq
        }

        Flickable {
            width: parent.width
            height: {
                var tempHeight = 0
                for (var i = 0; i < parent.children.length - 1; i++) {
                    tempHeight += parent.children[i].height
                }
                return parent.height - tempHeight
            }
            contentWidth: window.width
            contentHeight: height
            clip: true
            ChartView {
                id: chartView
                width: window.width
                height: parent.height
                antialiasing: true
                legend.visible: false
            }
        }
    }
}
