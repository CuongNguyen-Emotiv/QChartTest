#include "ChartViewController.h"
#include <QValueAxis>

static const QString QML_CHART_VIEW_CLASS_NAME = "DeclarativeChart";
static const char* QML_ENUM_SERIES_TYPE_NAME = "SeriesType";
static const char* QML_ENUM_SERIES_TYPE_KEY = "SeriesTypeLine";
static const char* QML_CHART_VIEW_CREATE_SERIES_METHOD = "createSeries";
static const int CHART_RANGE = 10;

ChartViewController::~ChartViewController()
{
    emit stopDataProducer();
    if (m_dataProducerThread) {
        m_dataProducerThread->quit();
        m_dataProducerThread->wait();
    }
}

ChartViewController *ChartViewController::instance()
{
    static ChartViewController chartViewController;
    return &chartViewController;
}

void ChartViewController::setChartView(QQuickItem *chartView)
{
    if(!chartView)
        return;
    const QMetaObject* metaObject = chartView->metaObject();
    if (QString(metaObject->className()) != QML_CHART_VIEW_CLASS_NAME)
        return;
    m_chartView = chartView;
    m_series = createLineSeries(0);
    emit startDataProducer();
}

void ChartViewController::addDataPoint(double x, double y)
{
    m_series->append(x, y);
}

void ChartViewController::updateChartView()
{
    int count = m_series->count();
    int max = m_axisX->max();
    if (count > max) {
        m_axisX->setMax(count);
        m_axisX->setMin(count - DATA_POINTS);
    }
}

ChartViewController::ChartViewController(QObject *parent)
    : QObject{parent}
{
    connect(this, &ChartViewController::startDataProducer, &m_dataProducer, &DataProducer::start);
    connect(this, &ChartViewController::stopDataProducer, &m_dataProducer, &DataProducer::stop);
    connect(&m_dataProducer, &DataProducer::addDataPoint, this, &ChartViewController::addDataPoint);
    connect(&m_dataProducer, &DataProducer::updateChartView, this, &ChartViewController::updateChartView);
    m_dataProducerThread = new QThread(this);
    m_dataProducerThread->start();
    m_dataProducer.moveToThread(m_dataProducerThread);
}

QLineSeries *ChartViewController::createLineSeries(int index)
{
    m_axisX = new QValueAxis();
    m_axisX->setMax(DATA_POINTS);
    m_axisX->setMin(0);
    m_axisX->setLabelsVisible(false);

    QValueAxis* axisY = new QValueAxis();
    axisY->setMin(index);
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
                              Q_ARG(QString, QString::number(index)),
                              Q_ARG(QAbstractAxis *, m_axisX),
                              Q_ARG(QAbstractAxis *, axisY));
    series->setUseOpenGL(true);

    return (QLineSeries*) series;
}
