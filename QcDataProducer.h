#ifndef QCDATAPRODUCER_H
#define QCDATAPRODUCER_H

#include <QObject>
#include <QTimer>
#include <QLineSeries>
#include "Constant.h"

class QcDataProducer : public QObject
{
    Q_OBJECT
public:
    explicit QcDataProducer(double yStartPosition = 0.0, QObject *parent = nullptr);
    ~QcDataProducer();
    void setPointsPerSec(int pointsPerSec);

signals:
    void updateChart(QList<QPointF> points);

public slots:
    void start();
    void stop();

private:
    QTimer *m_timerPointProducer = nullptr;
    QTimer *m_timerUpdateChartView = nullptr;
    int m_PointsPerSec = LOW_POINTS_PER_SEC;
    QList<QPointF> mCurrentPoints;
    QList<double> mNewY;
    double m_yStartPosition = 0;
};

#endif // QCDATAPRODUCER_H
