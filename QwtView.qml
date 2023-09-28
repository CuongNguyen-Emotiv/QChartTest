import QtQuick
import Emotiv.QwtChart 1.0
import Emotiv.QwtController 1.0

Item {
    width: parent.width
    height: parent.height

    QwtChart {
        id: qwtChart
        width: parent.width
        height: parent.height
        curveNumber: comboboxChartNumber.currentIndex
    }

    QwtController {
        id: qwtController
    }

    Connections {
        target: startButton
        function onClicked() {
            qwtController.setPointsPerSec(comboboxPointsPerSec.textAt(comboboxPointsPerSec.currentIndex))
            qwtController.createDataProducers(qwtChart, comboboxChartNumber.currentIndex)
        }
    }
}
