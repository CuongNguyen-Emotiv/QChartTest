#include "LineSeries.h"

LineSeries::LineSeries(DataProducer *dataProducer, QLineSeries* lineSeries, QObject *parent)
    : QObject{parent}
{
    m_lineSeries = lineSeries;
    m_lineSeries->setProperty("width", 0.5);
    connect(dataProducer, &DataProducer::updateChart, this, &LineSeries::updateChart);
    connect(this, &QObject::destroyed, dataProducer, &QObject::deleteLater);
}

LineSeries::~LineSeries()
{

}

void LineSeries::updateChart(QList<QPointF> points)
{
    m_lineSeries->replace(points);
}
