#include "QcDataProducer.h"
#include <QPointF>
#include <cstdlib>

QcDataProducer::QcDataProducer(int lineSeriesNumber, double pointsPerSec, QObject *parent)
    : DataProducer(lineSeriesNumber, pointsPerSec, parent)
{
    m_currentPointsList.resize(m_lineSeriesNumber);
    m_newPointsList.resize(m_lineSeriesNumber);
}

QcDataProducer::~QcDataProducer()
{

}

void QcDataProducer::producePoints()
{
    double currentTime = getCurrentTime();
    for (int i = 0; i < m_lineSeriesNumber; ++i) {
        m_newPointsList[i].append(QPointF(currentTime, randomDouble(i*CHART_RANGE, (i+1)*CHART_RANGE)));
    }
}

void QcDataProducer::updateChartView()
{
    int removePoints = m_currentPointsList[0].count() + m_newPointsList[0].count() - m_pointsPerSec * DATA_SECS;
    if (removePoints > 0) {
        for (auto& currentPoints : m_currentPointsList) {
            currentPoints.remove(0, removePoints);
        }
    }
    for (int i = 0; i < m_currentPointsList.count(); ++i) {
        m_currentPointsList[i].append(m_newPointsList[i]);
        m_newPointsList[i].clear();
    }
    emit updateChart(m_currentPointsList);
}


void QcDataProducer::cleanOldData()
{
    m_currentPointsList.clear();
    m_newPointsList.clear();
    m_currentPointsList.resize(m_lineSeriesNumber);
    m_newPointsList.resize(m_lineSeriesNumber);
}
