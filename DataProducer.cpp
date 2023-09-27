#include "DataProducer.h"

DataProducer::DataProducer(int startYPosition, int pointsPerSec, QObject *parent)
    : QObject{parent}
{
    m_startYPosition = startYPosition;
    m_pointsPerSec = pointsPerSec;
}

void DataProducer::start()
{
    stop();
    m_timerPointProducer = new QTimer();
    m_timerUpdateChartView = new QTimer();

    connect(m_timerPointProducer, &QTimer::timeout, this, &DataProducer::producePoints);
    connect(m_timerUpdateChartView, &QTimer::timeout, this, &DataProducer::updateChartView);

    m_timerPointProducer->start(1000 / m_pointsPerSec);
    m_timerUpdateChartView->start(1000 / REFRESH_RATE);
}

void DataProducer::stop()
{
    cleanOldData();
    if (m_timerPointProducer) {
        m_timerPointProducer->stop();
        delete m_timerPointProducer;
        m_timerPointProducer = nullptr;
    }
    if (m_timerUpdateChartView) {
        m_timerUpdateChartView->stop();
        delete m_timerUpdateChartView;
        m_timerUpdateChartView = nullptr;
    }
}
