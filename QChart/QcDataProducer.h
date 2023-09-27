#ifndef QCDATAPRODUCER_H
#define QCDATAPRODUCER_H

#include <QObject>
#include <QTimer>
#include <QLineSeries>
#include "Constant.h"
#include "DataProducer.h"

class QcDataProducer : public DataProducer
{
    Q_OBJECT
public:
    explicit QcDataProducer(double yStartPosition = 0.0, int pointsPerSec = LOW_POINTS_PER_SEC, QObject *parent = nullptr);
    ~QcDataProducer();

signals:
    void updateChart(QList<QPointF> points);

    // DataProducer interface
protected slots:
    virtual void producePoints() override;
    virtual void updateChartView() override;
    virtual void cleanOldData() override;

private:
    QList<QPointF> mCurrentPoints;
    QList<double> mNewY;
};

#endif // QCDATAPRODUCER_H
