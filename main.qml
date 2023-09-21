import QtQuick
import QtQuick.Window
import QtCharts 2.5
import Emotiv.ChartViewController 1.0
import QtQuick.Controls

Window {
    id: window
    width: 750/2
    height: 1334/2
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
                anchors.verticalCenter: textPointsPerSec.verticalCenter
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
                model: 32
                anchors.verticalCenter: textChartNumber.verticalCenter
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
            }
            Button {
                text: "Stop"
                onClicked: {
                    ChartViewController.stopDataProducer()
                }
            }
        }

        Flickable {
            width: parent.width
            height: window.height/2
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
                    }
                    onModelChanged: chartViews = []
                }
            }
        }
    }
}
