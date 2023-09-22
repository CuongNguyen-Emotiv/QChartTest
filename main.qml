import QtQuick
import QtQuick.Window
import QtCharts 2.5
import Emotiv.ChartViewController 1.0
import QtQuick.Controls
import Emotiv.FPSText 1.0

Window {
    id: window
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("Hello World")

    readonly property int chartHeight: width/2

    FPSText{
        id: fpsText
        width: 1
        height: 1
    }

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
                    ChartViewController.setPointsPerSec(comboboxPointsPerSec.currentText)
                    repeaterChartView.model = 0
                    repeaterChartView.model = comboboxChartNumber.currentIndex
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
            text: "FPS: " + fpsText.fps.toFixed(2)
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
            contentHeight: chartHeight * repeaterChartView.model
            flickableDirection: Flickable.VerticalFlick
            clip: true
            Column {
                Repeater {
                    id: repeaterChartView
                    property var chartViews: []
                    model: 1
                    delegate: ChartView {
                        id: chartView
                        width: window.width
                        height: chartHeight
                        antialiasing: true
                        legend.visible: false

                        Component.onCompleted: {
                            repeaterChartView.chartViews.push(chartView)
                            if (index === repeaterChartView.count - 1) {
                                ChartViewController.setChartViews(repeaterChartView.chartViews)
                            }
                        }

                        Text {
                            text: index + 1
                            anchors.verticalCenter: parent.verticalCenter
                            padding: 10
                        }
                    }
                    onModelChanged: chartViews = []
                }
            }
        }
    }
}
