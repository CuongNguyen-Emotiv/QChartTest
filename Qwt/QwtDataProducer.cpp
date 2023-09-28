#include "QwtDataProducer.h"
#include "QtCore/qdebug.h"

QwtDataProducer::QwtDataProducer(int lineSeriesNumber, int pointsPerSec, QObject *parent)
    : DataProducer{lineSeriesNumber, pointsPerSec, parent}
{
    m_currentXDataList.resize(lineSeriesNumber);
    m_currentYDataList.resize(lineSeriesNumber);
    m_newXDataList.resize(lineSeriesNumber);
    m_newYDataList.resize(lineSeriesNumber);
}


void QwtDataProducer::producePoints()
{
    double currentTime = getCurrentTime();
    for (int i = 0; i < m_lineSeriesNumber; ++i) {
        m_newXDataList[i].append(currentTime);
        m_newYDataList[i].append(randomDouble(i*CHART_RANGE, (i+1)*CHART_RANGE));
    }
}

void QwtDataProducer::updateChartView()
{
    int removePoints = m_currentXDataList[0].count() + m_newXDataList[0].count() - m_pointsPerSec * DATA_SECS;
    if (removePoints > 0) {
        for (auto& currentXData : m_currentXDataList) {
            currentXData.remove(0, removePoints);
        }
        for (auto& currentYData : m_currentYDataList) {
            currentYData.remove(0, removePoints);
        }
    }
    for (int i = 0; i < m_currentXDataList.count(); ++i) {
        m_currentXDataList[i].append(m_newXDataList[i]);
        m_currentYDataList[i].append(m_newYDataList[i]);
        m_newXDataList[i].clear();
        m_newYDataList[i].clear();
    }
    emit updateChart(m_currentXDataList, m_currentYDataList);
}

void QwtDataProducer::cleanOldData()
{
    m_currentXDataList.clear();
    m_currentYDataList.clear();
    m_newXDataList.clear();
    m_newYDataList.clear();
    m_currentXDataList.resize(m_lineSeriesNumber);
    m_currentYDataList.resize(m_lineSeriesNumber);
    m_newXDataList.resize(m_lineSeriesNumber);
    m_newYDataList.resize(m_lineSeriesNumber);
}
