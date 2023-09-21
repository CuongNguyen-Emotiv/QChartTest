#include "DataProducer.h"
#include <cstdlib>

DataProducer::DataProducer(QObject *parent)
    : QObject{parent}
{

}

void DataProducer::setPointsPerSec(int pointsPerSec)
{
    m_PointsPerSec = pointsPerSec;
}

void DataProducer::start()
{
    stop();
    m_timerPointProducer = new QTimer();
    m_timerUpdateChartView = new QTimer();
    connect(m_timerPointProducer, &QTimer::timeout, this, [this](){
        ++m_count;
        emit addDataPoint(m_count, (double)rand() / RAND_MAX * 10.0);
    });
    connect(m_timerUpdateChartView, &QTimer::timeout, this, &DataProducer::updateChartView);
    m_timerPointProducer->start(1000 / m_PointsPerSec);
    m_timerUpdateChartView->start(1000 / REFRESH_RATE);
}

void DataProducer::stop()
{
    m_count = 0;
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
