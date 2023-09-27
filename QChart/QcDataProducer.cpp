#include "QcDataProducer.h"
#include <QPointF>
#include <cstdlib>

QcDataProducer::QcDataProducer(double yStartPosition, int pointsPerSec, QObject *parent)
    : DataProducer(yStartPosition, pointsPerSec, parent)
{

}

QcDataProducer::~QcDataProducer()
{

}

void QcDataProducer::producePoints()
{
    mNewY.append((double)rand() / RAND_MAX * 10.0 + m_startYPosition);
}

void QcDataProducer::updateChartView()
{
    int removePoints = mCurrentPoints.count() + mNewY.count() - m_pointsPerSec * DATA_SECS;
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
}


void QcDataProducer::cleanOldData()
{
    mCurrentPoints.clear();
    mNewY.clear();
}
