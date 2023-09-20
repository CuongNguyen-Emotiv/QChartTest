import QtQuick
import QtQuick.Window
import QtCharts 2.5

Window {
    id: window
    width: 750/2
    height: 1334/2
    visible: true
    title: qsTr("Hello World")

    readonly property int chartHeight: width/2

    Flickable {
        width: parent.width
        height: parent.height
        contentWidth: window.width
        contentHeight: chartHeight * repeater.model
        flickableDirection: Flickable.VerticalFlick
        Column {
            id: column
            Repeater {
                id: repeater
                model: 1

                delegate: ChartView {
                    id: chartView
                    width: window.width
                    height: chartHeight
                    anchors.margins: 10
                    antialiasing: true
                    legend.visible: false

                    LineSeries {
                        id: series
                        name: "LineSeries1"
                        axisX: ValueAxis
                        {
                            min: 0
                            max: 180
                            labelsVisible: false
                        }

                        axisY: ValueAxis
                        {
                            min: -1
                            max: 11
                            labelsVisible: false
                        }

                        onCountChanged: {
                            if (series.count > axisX.max)
                            {
                                axisX.min = axisX.min + 1
                                axisX.max = axisX.max + 1
                            }
                        }
                    }

                    Timer {
                        property int currentX: 0
                        interval: 10
                        running: true
                        repeat: true
                        onTriggered: {
                            // Append the new point to the LineSeries
                            ++currentX;
                            series.append(currentX, Math.random() * 10)
                        }
                    }
                }
            }
        }
    }
}
