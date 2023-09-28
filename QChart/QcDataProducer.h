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
    explicit QcDataProducer(int lineSeriesNumber, double pointsPerSec = LOW_POINTS_PER_SEC, QObject *parent = nullptr);
    ~QcDataProducer();

signals:
    void updateChart(QList<QList<QPointF>> pointsList);

    // DataProducer interface
protected slots:
    virtual void producePoints() override;
    virtual void updateChartView() override;
    virtual void cleanOldData() override;

private:
    QList<QList<QPointF>> m_currentPointsList;
    QList<QList<QPointF>> m_newPointsList;
};

#endif // QCDATAPRODUCER_H
