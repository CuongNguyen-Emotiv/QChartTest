#include "DataProducer.h"
#include <cstdlib>

DataProducer::DataProducer(QObject *parent)
    : QObject{parent}
{

}

void DataProducer::start()
{
    m_timerPointProducer = new QTimer();
    m_timerUpdateChartView = new QTimer();
    connect(m_timerPointProducer, &QTimer::timeout, this, [this](){
        ++m_count;
        emit addDataPoint(m_count, (double)rand() / RAND_MAX * 10.0);
    });
    connect(m_timerUpdateChartView, &QTimer::timeout, this, &DataProducer::updateChartView);
    m_timerPointProducer->start(1000 / DATA_POINTS_PER_SEC);
    m_timerUpdateChartView->start(1000 / REFRESH_RATE);
}

void DataProducer::stop()
{
    m_timerPointProducer->stop();
    m_timerUpdateChartView->stop();
    delete m_timerPointProducer;
    delete m_timerUpdateChartView;
}
