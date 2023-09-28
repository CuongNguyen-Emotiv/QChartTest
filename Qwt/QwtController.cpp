#include "QwtController.h"
#include "QwtDataProducer.h"
#include <random>

QwtController::~QwtController()
{
    m_lineSeriesList.clear();
}

void QwtController::createDataProducers(QwtChart *qwtChart, int numberOfLineSeries)
{
    if (qwtChart == nullptr || numberOfLineSeries <= 0)
        return;
    m_lineSeriesList.clear();
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
        curve->setPen(QColor(randomInt(0,255), randomInt(0,255), randomInt(0,255)), 0.5);
        curve->setRenderHint(QwtPlotItem::RenderAntialiased, true); // Enable antialiasing for curves

        curve->attach(qwtChart->plot());
        m_lineSeriesList.append(curve);
    }
    emit startDataProducer();
}

int QwtController::randomInt(int low, int high)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist(low, high);
    return dist(gen);
}

void QwtController::updateChart(QList<QVector<double> > xDataList, QList<QVector<double> > yDataList)
{
    for (int i = 0; i < xDataList.count(); ++i)
    {
        m_lineSeriesList[i]->setSamples(xDataList[i], yDataList[i]);
    }
    m_qwtChart->plot()->replot();
    m_qwtChart->update();
}
