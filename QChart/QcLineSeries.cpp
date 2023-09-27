#include "QcLineSeries.h"

QcLineSeries::QcLineSeries(QcDataProducer *dataProducer, QLineSeries* lineSeries, QObject *parent)
    : QObject{parent}
{
    m_lineSeries = lineSeries;
    m_dataProducer = dataProducer;
    m_lineSeries->setProperty("width", 0.5);
    connect(dataProducer, &QcDataProducer::updateChart, this, &QcLineSeries::updateChart);
    connect(this, &QObject::destroyed, dataProducer, &QObject::deleteLater);
}

QcLineSeries::~QcLineSeries()
{
    disconnect(m_dataProducer, &QcDataProducer::updateChart, this, &QcLineSeries::updateChart);
}

void QcLineSeries::updateChart(QList<QPointF> points)
{
    if (m_lineSeries) {
        m_lineSeries->replace(points);
    }
}
