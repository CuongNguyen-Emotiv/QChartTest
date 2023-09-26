import QtQuick
import QtCharts 2.5
import Emotiv.QcViewController 1.0

ChartView {
    id: chartView
    width: parent.width
    height: parent.height
    antialiasing: true
    legend.visible: false

    readonly property double chartRange: 10
    readonly property double dataSecs: 5

    ValuesAxis {
        id: valueAxisX
        labelsVisible: false
        gridVisible: false
    }

    ValuesAxis {
        id: valueAxisY
        labelsVisible: false
        gridVisible: false
    }

    Connections {
        target: startButton
        function onClicked() {
            chartView.removeAllSeries();
            QcViewController.setPointsPerSec(comboboxPointsPerSec.textAt(comboboxPointsPerSec.currentIndex))

            valueAxisX.min = 0
            valueAxisX.max = comboboxPointsPerSec.textAt(comboboxPointsPerSec.currentIndex) * dataSecs

            valueAxisY.min = 0
            valueAxisY.max = chartRange * comboboxChartNumber.currentIndex
            var seriesList = [];
            for (var i = 0; i < comboboxChartNumber.currentIndex; ++i) {
                var lineSeries = chartView.createSeries(ChartView.SeriesTypeLine, "Series " + i, valueAxisX, valueAxisY)
                seriesList.push(lineSeries)
            }
            QcViewController.createDataProducers(seriesList)
        }
    }

    Connections {
        target: stopButton
        function onClicked() {
            QcViewController.stopDataProducer()
        }
    }

    Component.onDestruction: {
        QcViewController.cleanUp();
    }
}
