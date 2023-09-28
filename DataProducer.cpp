#include "DataProducer.h"
#include <random>
#include <QDateTime>

DataProducer::DataProducer(int lineSeriesNumber, int pointsPerSec, QObject *parent)
    : QObject{parent}
{
    m_lineSeriesNumber = lineSeriesNumber;
    m_pointsPerSec = pointsPerSec;
}

double DataProducer::randomDouble(double min, double max) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

double DataProducer::getCurrentTime() const
{
    QDateTime now = QDateTime::currentDateTime();
    return static_cast<double>(now.toMSecsSinceEpoch()) / 1000.0;
}

void DataProducer::start()
{
    stop();
    m_timerPointProducer = new QTimer();
    m_timerUpdateChartView = new QTimer();

    connect(m_timerPointProducer, &QTimer::timeout, this, &DataProducer::producePoints);
    connect(m_timerUpdateChartView, &QTimer::timeout, this, &DataProducer::updateChartView);

    m_timerPointProducer->start(ONE_SEC_MS / m_pointsPerSec);
    m_timerUpdateChartView->start(ONE_SEC_MS / REFRESH_RATE);
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
