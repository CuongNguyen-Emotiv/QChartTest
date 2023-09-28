#ifndef CONSTANT_H
#define CONSTANT_H

#include <QObject>

static const int LOW_POINTS_PER_SEC = 128;
static const int HIGH_POINTS_PER_SEC = 256;
static const int CHART_RANGE = 10;
static const int DATA_SECS = 5;
static const int REFRESH_RATE = 16;
static const QString QTCHART_VIEW = "Qt Chart View";
static const QString QWT_VIEW = "Qwt View";
static const int MAX_CHART_NUMBER = 65;
static const int ONE_SEC_MS = 1024;

class Constant : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE int lowPointsPerSec();
    Q_INVOKABLE int highPointsPerSec();
    Q_INVOKABLE int chartRange();
    Q_INVOKABLE int dataSecs();
    Q_INVOKABLE int refreshRate();
    Q_INVOKABLE QString qtChartView();
    Q_INVOKABLE QString qwtView();
    Q_INVOKABLE int maxChartNumber();
};

#endif // CONSTANT_H
