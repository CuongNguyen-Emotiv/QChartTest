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
    }

    Connections {
        target: startButton
        function onClicked() {
            QwtController.setPointsPerSec(comboboxPointsPerSec.textAt(comboboxPointsPerSec.currentIndex))
            QwtController.createDataProducers(qwtChart, comboboxChartNumber.currentIndex)
        }
    }
}
