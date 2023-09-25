#include "DataProducer.h"
#include <QPointF>
#include <cstdlib>

DataProducer::DataProducer(double yStartPosition, QObject *parent)
    : QObject{parent}
{
    m_yStartPosition = yStartPosition;
}

DataProducer::~DataProducer()
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
        mNewY.append((double)rand() / RAND_MAX * 10.0 + m_yStartPosition);
    });
    connect(m_timerUpdateChartView, &QTimer::timeout, this, [this](){
        int removePoints = mCurrentPoints.count() + mNewY.count() - m_PointsPerSec * DATA_SECS;
        if (removePoints > 0) {
            mCurrentPoints.remove(0, removePoints);
            for (auto& point : mCurrentPoints) {
                point.setX(point.x() - removePoints);
            }
        }
        for (const auto& y : mNewY) {
            mCurrentPoints.append(QPointF(mCurrentPoints.count(), y));
        }
        mNewY.clear();
        emit updateChart(mCurrentPoints);
    });
    m_timerPointProducer->start(1000 / m_PointsPerSec);
    m_timerUpdateChartView->start(1000 / REFRESH_RATE);
}

void DataProducer::stop()
{
    mCurrentPoints.clear();
    mNewY.clear();
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
