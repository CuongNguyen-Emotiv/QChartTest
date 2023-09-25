#ifndef CHARTVIEWCONTROLLER_H
#define CHARTVIEWCONTROLLER_H

#include "DataProducer.h"
#include <QValueAxis>
#include <QObject>
#include <QQuickItem>
#include <QLineSeries>
#include <QThread>
#include "LineSeries.h"

class ChartViewController : public QObject
{
    Q_OBJECT
public:
    ~ChartViewController();
    static ChartViewController *instance();
    Q_INVOKABLE void setPointsPerSec(int pointsPerSec);
    Q_INVOKABLE void createSeries(QQuickItem* chartView, int lineSeriesNumber);

signals:
    void startDataProducer();
    Q_INVOKABLE void stopDataProducer();

private:
    explicit ChartViewController(QObject *parent = nullptr);

    QLineSeries* createLineSeries();

private:
    QList<QThread*> m_dataProducerThreads;

    QList<DataProducer*> m_dataProducers;
    QList<LineSeries*> m_lineSeriesList;

    QValueAxis m_axisX;
    QValueAxis m_axisY;

    int m_pointPerSec = DEFAULT_POINTS_PER_SEC;
};

#endif // CHARTVIEWCONTROLLER_H
