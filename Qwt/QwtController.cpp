#include "QwtController.h"
#include "QwtDataProducer.h"

QwtController::QwtController(QObject *parent) : Controller(parent)
{

}

void QwtController::createDataProducers(QwtChart *qwtChart, int numberOfLineSeries)
{
    if (qwtChart == nullptr || numberOfLineSeries <= 0)
        return;
    createDataProducerThread();
    m_qwtChart = qwtChart;
    m_dataProducer = new QwtDataProducer(numberOfLineSeries, m_pointPerSec);
    connect(m_dataProducer, &QwtDataProducer::updateChart, this, &QwtController::updateChart);
    m_dataProducer->moveToThread(m_dataProducerThread);
    connect(this, &QwtController::startDataProducer, m_dataProducer, &QwtDataProducer::start);
    connect(this, &QwtController::stopDataProducer, m_dataProducer, &QwtDataProducer::stop);
    connect(this, &QwtController::stopDataProducer, m_dataProducer, &QwtDataProducer::deleteLater);
    for (int i = 0; i < numberOfLineSeries; i++)
    {
        QwtPlotCurve *curve = new QwtPlotCurve();
        curve->attach(qwtChart->qwtPlot());
        m_lineSeriesList.append(curve);
    }
    emit startDataProducer();
}

void QwtController::updateChart(QList<QVector<double> > xDataList, QList<QVector<double> > yDataList)
{
    for (int i = 0; i < xDataList.count(); ++i)
    {
        m_lineSeriesList[i]->setSamples(xDataList[i], yDataList[i]);
    }
    m_qwtChart->qwtPlot()->replot();
    m_qwtChart->update();
}
