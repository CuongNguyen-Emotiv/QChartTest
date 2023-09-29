#include "ProDataProceducer.h"

ProDataProceducer::ProDataProceducer(int lineSeriesNumber, int pointsPerSec, QObject *parent)
    : DataProducer{lineSeriesNumber, pointsPerSec, parent}
{
    for (int i = 0; i < lineSeriesNumber; ++i) {
        m_xDataList.append(QVector<double>());
        m_yDataList.append(QVector<double>());
        m_newXList.append(QVector<double>());
        m_newYList.append(QVector<double>());
    }
}


void ProDataProceducer::producePoints()
{
    for (auto& newX : m_newXList) {
        newX.append(m_count);
    }
    for (int i = 0; i < m_newYList.size(); ++i) {
        m_newYList[i].append(randomDouble(i * CHART_RANGE, (i+1) * CHART_RANGE));
    }
    ++m_count;
}

void ProDataProceducer::updateChartView()
{
    int removePoints = m_xDataList[0].size() + m_yDataList[0].size() - m_pointsPerSec * DATA_SECS;

    //y
    if (removePoints > 0) {
        for (int i = 0; i < m_yDataList.size(); ++i) {
            m_yDataList[i].remove(0, removePoints);
        }
    }
    for (int i = 0; i < m_yDataList.size(); ++i) {
        m_yDataList[i].append(m_newYList[i]);
        m_newYList[i].clear();
    }

    //x
    if (removePoints <= 0) {
        for (int i = 0; i < m_xDataList.size(); ++i) {
            m_xDataList[i].append(m_newXList[i]);
            m_newXList[i].clear();
        }
    }
    for (int i = 0; i < m_newXList.size(); ++i) {
        m_newXList[i].clear();
    }

    emit updateChart(m_xDataList, m_yDataList);
}

void ProDataProceducer::cleanOldData()
{
    m_xDataList.clear();
    m_yDataList.clear();
    m_newXList.clear();
    m_newYList.clear();

    for (int i = 0; i < m_lineSeriesNumber; ++i) {
        m_xDataList.append(QVector<double>());
        m_yDataList.append(QVector<double>());
        m_newXList.append(QVector<double>());
        m_newYList.append(QVector<double>());
    }
}
