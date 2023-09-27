#include "QwtController.h"
#include "QwtDataProducer.h"

void QwtController::createDataProducers(QwtChart *qwtChart, int numberOfLineSeries)
{
    for (int i = 0; i < numberOfLineSeries; i++)
    {
        QwtPlotCurve *curve = new QwtPlotCurve();
        curve->attach(qwtChart->qwtPlot());

        QwtDataProducer *dataProducer = new QwtDataProducer();

        QwtLineSeries *lineSeries = new QwtLineSeries(curve, dataProducer);
        m_lineSeriesList.append(lineSeries);
    }
}
