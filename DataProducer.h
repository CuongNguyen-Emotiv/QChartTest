#ifndef DATAPRODUCER_H
#define DATAPRODUCER_H

#include <QObject>
#include <QTimer>

static const int DATA_POINTS_PER_SEC = 256;
static const int DATA_SECS = 5;
static const int DATA_POINTS = DATA_POINTS_PER_SEC * DATA_SECS;
static const int REFRESH_RATE = 16;

class DataProducer : public QObject
{
    Q_OBJECT
public:
    explicit DataProducer(QObject *parent = nullptr);

signals:
    void addDataPoint(double x, double y);
    void updateChartView();

public slots:
    void start();
    void stop();

private:
    QTimer *m_timerPointProducer = nullptr;
    QTimer *m_timerUpdateChartView = nullptr;
    unsigned int m_count = 0;
};

#endif // DATAPRODUCER_H
