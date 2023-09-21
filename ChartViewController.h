#ifndef CHARTVIEWCONTROLLER_H
#define CHARTVIEWCONTROLLER_H

#include "DataProducer.h"
#include "QtCharts/qvalueaxis.h"
#include <QObject>
#include <QQuickItem>
#include <QLineSeries>
#include <QThread>

class ChartViewController : public QObject
{
    Q_OBJECT
public:
    ~ChartViewController();
    static ChartViewController *instance();
    Q_INVOKABLE void setChartView(QQuickItem *chartView);

private slots:
    void addDataPoint(double x, double y);
    void updateChartView();

signals:
    void startDataProducer();
    void stopDataProducer();

private:
    explicit ChartViewController(QObject *parent = nullptr);

    QLineSeries* createLineSeries(int index);

private:
    QQuickItem *m_chartView = nullptr;
    QLineSeries* m_series;
    QValueAxis* m_axisX;

    DataProducer m_dataProducer;
    QThread* m_dataProducerThread;
};

#endif // CHARTVIEWCONTROLLER_H
