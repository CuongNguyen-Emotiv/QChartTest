import QtQuick
import Emotiv.QuickQwtPlot 1.0
import Emotiv.QuickCurve 1.0

Item {
    width: parent.width
    height: parent.height

    QuickQwtPlot {
        id: quickQwtPlot
        width: parent.width
        height: parent.height
    }

    QuickCurve {
        id: quickCurve
        Component.onCompleted: {
            createCurves(comboboxChartNumber.currentIndex, comboboxPointsPerSec.textAt(comboboxPointsPerSec.currentIndex))
            attach(quickQwtPlot)
        }
    }
}
