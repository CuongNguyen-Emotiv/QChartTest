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

void ChartViewCpp::addDataPoint(double x, double y)
{
    m_series->append(x, y);
}

void ChartViewCpp::updateChartView()
{
    int count = m_series->count();
    int max = m_axisX->max();
    if (count > max) {
        m_axisX->setMax(count);
        m_axisX->setMin(count - m_pointsPerSec * DATA_SECS);
        m_series->removePoints(0, count - max);
    }
}

void ChartViewCpp::setPointsPerSec(int pointsPerSec)
{
    m_pointsPerSec = pointsPerSec;
}

QLineSeries *ChartViewCpp::createLineSeries()
{
    m_axisX = new QValueAxis();
    m_axisX->setMax(m_pointsPerSec * DATA_SECS);
    m_axisX->setMin(0);
    m_axisX->setLabelsVisible(false);

    QValueAxis* axisY = new QValueAxis();
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
                              Q_ARG(QAbstractAxis *, m_axisX),
                              Q_ARG(QAbstractAxis *, axisY));
    series->setUseOpenGL(true);

    return (QLineSeries*) series;
}
