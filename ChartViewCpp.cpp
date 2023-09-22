#include "ChartViewCpp.h"

ChartViewCpp::ChartViewCpp(QObject *parent)
    : QObject{parent}
{

}

void ChartViewCpp::setChartView(QQuickItem *chartView)
{
    if(!chartView)
        return;
    const QMetaObject* metaObject = chartView->metaObject();
    if (QString(metaObject->className()) != QML_CHART_VIEW_CLASS_NAME)
        return;
    m_chartView = chartView;
    m_series = createLineSeries();
}

void ChartViewCpp::setPointsPerSec(int pointsPerSec)
{
    m_pointsPerSec = pointsPerSec;
}

void ChartViewCpp::updateChart(const QList<QPointF> &points)
{
    // replace() for the best performance
    m_series->replace(points);
}

QLineSeries *ChartViewCpp::createLineSeries()
{
    axisX = new QValueAxis(this);
    axisX->setMax(m_pointsPerSec * DATA_SECS);
    axisX->setMin(0);
    axisX->setLabelsVisible(false);

    QValueAxis* axisY = new QValueAxis(this);
    axisY->setMin(0);
    axisY->setMax(axisY->min() + CHART_RANGE);
    axisY->setLabelsVisible(false);

    const QMetaObject* metaObject = m_chartView->metaObject();
    int enumIndex = metaObject->indexOfEnumerator(QML_ENUM_SERIES_TYPE_NAME);
    QMetaEnum metaEnum = metaObject->enumerator(enumIndex);
    int chartType = metaEnum.keyToValue(QML_ENUM_SERIES_TYPE_KEY);

    QAbstractSeries *series = nullptr;
    QMetaObject::invokeMethod(m_chartView, QML_CHART_VIEW_CREATE_SERIES_METHOD, Qt::DirectConnection,
                              Q_RETURN_ARG(QAbstractSeries *, series),
                              Q_ARG(int, chartType),
                              Q_ARG(QString, ""),
                              Q_ARG(QAbstractAxis *, axisX),
                              Q_ARG(QAbstractAxis *, axisY));

    // for the best perfomance
    series->setUseOpenGL(true);

    connect(this, &QLineSeries::destroyed, series, &QAbstractSeries::deleteLater);

    return (QLineSeries*) series;
}
