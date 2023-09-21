#ifndef CHARTVIEWCPP_H
#define CHARTVIEWCPP_H

#include <QQuickItem>
#include <QObject>
#include <QLineSeries>
#include <QValueAxis>
#include "Constants.h"

class ChartViewCpp : public QObject
{
    Q_OBJECT
public:
    explicit ChartViewCpp(QObject *parent = nullptr);
    void setChartView(QQuickItem *chartView);
    void addDataPoint(double x, double y);
    void updateChartView();
    void setPointsPerSec(int pointsPerSec);

private:
    QLineSeries* createLineSeries();

signals:

private:
    QQuickItem* m_chartView;
    QLineSeries* m_series;
    QValueAxis* m_axisX;

    int m_pointsPerSec = DEFAULT_POINTS_PER_SEC;
};

#endif // CHARTVIEWCPP_H
