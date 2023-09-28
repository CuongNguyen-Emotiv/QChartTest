#ifndef DATAPRODUCER_H
#define DATAPRODUCER_H

#include <QObject>
#include <QTimer>

#include "Constant.h"

class DataProducer : public QObject
{
    Q_OBJECT
public:
    explicit DataProducer(int lineSeriesNumber, int pointsPerSec, QObject *parent = nullptr);

protected:
    double randomDouble(double min, double max) const;
    double getCurrentTime() const;

signals:

public slots:
    void start();
    void stop();

protected slots:
    virtual void producePoints() = 0;
    virtual void updateChartView() = 0;
    virtual void cleanOldData() = 0;

protected:
    int m_lineSeriesNumber = 0;
    int m_pointsPerSec = LOW_POINTS_PER_SEC;

private:
    QTimer *m_timerPointProducer = nullptr;
    QTimer *m_timerUpdateChartView = nullptr;
};

#endif // DATAPRODUCER_H
