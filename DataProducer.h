#ifndef DATAPRODUCER_H
#define DATAPRODUCER_H

#include <QObject>
#include <QTimer>
#include "Constants.h"

class DataProducer : public QObject
{
    Q_OBJECT
public:
    explicit DataProducer(QObject *parent = nullptr);
    void setPointsPerSec(int pointsPerSec);

signals:
    void updateChart(QList<QPointF> points);

public slots:
    void start();
    void stop();

private:
    QTimer *m_timerPointProducer = nullptr;
    QTimer *m_timerUpdateChartView = nullptr;
    int m_PointsPerSec = DEFAULT_POINTS_PER_SEC;
    QList<QPointF> mCurrentPoints;
    QList<double> mNewY;
};

#endif // DATAPRODUCER_H
