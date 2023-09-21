import QtQuick
import QtQuick.Window
import QtCharts 2.5
import Emotiv.ChartViewController 1.0

Window {
    id: window
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("Hello World")

    readonly property int chartHeight: width/2

    Flickable {
        width: parent.width
        height: parent.height
        contentWidth: window.width
        contentHeight: chartView.height
        flickableDirection: Flickable.VerticalFlick
        ChartView {
            id: chartView
            width: window.width
            height: chartHeight
            antialiasing: true
            legend.visible: false

            Component.onCompleted: {
                ChartViewController.setChartView(chartView)
            }
        }
    }
}
