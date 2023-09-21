#ifndef CHARTVIEWCONTROLLER_H
#define CHARTVIEWCONTROLLER_H

#include "DataProducer.h"
#include <QValueAxis>
#include <QObject>
#include <QQuickItem>
#include <QLineSeries>
#include <QThread>
#include "ChartViewCpp.h"

class ChartViewController : public QObject
{
    Q_OBJECT
public:
    ~ChartViewController();
    static ChartViewController *instance();
    Q_INVOKABLE void setChartViews(QList<QQuickItem*> chartViews);
    Q_INVOKABLE void setPointsPerSec(int pointsPerSec);

signals:
    void startDataProducer();
    Q_INVOKABLE void stopDataProducer();

private:
    explicit ChartViewController(QObject *parent = nullptr);

    QLineSeries* createLineSeries();

private:
    QThread* m_dataProducerThread;

    QList<ChartViewCpp*> m_chartViews;
    QList<DataProducer*> m_dataProducers;

};

#endif // CHARTVIEWCONTROLLER_H
