#include "ChartViewController.h"
#include <QValueAxis>

ChartViewController::~ChartViewController()
{
    emit stopDataProducer();
    for (auto& thread : m_dataProducerThreads) {
        thread->quit();
        thread->wait();
        delete thread;
    }
    m_dataProducerThreads.clear();
}

ChartViewController *ChartViewController::instance()
{
    static ChartViewController chartViewController;
    return &chartViewController;
}

void ChartViewController::setPointsPerSec(int pointsPerSec)
{
    m_pointPerSec = pointsPerSec;
    m_axisX.setMax(m_pointPerSec * DATA_SECS);
    for (auto& dataProducer : m_dataProducers) {
        dataProducer->setPointsPerSec(pointsPerSec);
    }
}

void ChartViewController::createSeries(QQuickItem *chartView, int lineSeriesNumber)
{
    emit stopDataProducer();
    m_axisY.setMax(lineSeriesNumber * CHART_RANGE);
    m_axisX.setMax(m_pointPerSec * DATA_SECS);

    for (auto& lineSeries : m_lineSeriesList) {
        delete lineSeries;
    }
    m_lineSeriesList.clear();
    m_dataProducers.clear();

    const QMetaObject* metaObject = chartView->metaObject();
    if (QString(metaObject->className()) != QML_CHART_VIEW_CLASS_NAME)
        return;
    int enumIndex = metaObject->indexOfEnumerator(QML_ENUM_SERIES_TYPE_NAME);
    QMetaEnum metaEnum = metaObject->enumerator(enumIndex);
    int chartType = metaEnum.keyToValue(QML_ENUM_SERIES_TYPE_KEY);

    for (int i = 0; i < lineSeriesNumber; ++i) {
        QAbstractSeries *series = nullptr;
        QMetaObject::invokeMethod(chartView, QML_CHART_VIEW_CREATE_SERIES_METHOD, Qt::DirectConnection,
                                  Q_RETURN_ARG(QAbstractSeries *, series),
                                  Q_ARG(int, chartType),
                                  Q_ARG(QString, QString::number(i)),
                                  Q_ARG(QAbstractAxis *, &m_axisX),
                                  Q_ARG(QAbstractAxis *, &m_axisY));

        // for the best perfomance
        series->setUseOpenGL(true);

        DataProducer* dataProducer = new DataProducer(i * CHART_RANGE);
        dataProducer->moveToThread(m_dataProducerThreads[i % m_dataProducerThreads.count()]);
        dataProducer->setPointsPerSec(m_pointPerSec);
        connect(this, &ChartViewController::startDataProducer, dataProducer, &DataProducer::start);
        connect(this, &ChartViewController::stopDataProducer, dataProducer, &DataProducer::stop);

        LineSeries* lineSeries = new LineSeries(dataProducer, (QLineSeries*)series);

        m_lineSeriesList.append(lineSeries);
        m_dataProducers.append(dataProducer);
    }

    emit startDataProducer();
}

ChartViewController::ChartViewController(QObject *parent)
    : QObject{parent}
{
    m_axisX.setMin(0);
    m_axisX.setLabelsVisible(false);
    m_axisX.setGridLineVisible(false);

    m_axisY.setMin(0);
    m_axisY.setLabelsVisible(false);
    m_axisY.setGridLineVisible(false);

    unsigned int hardwareConcurrency = std::thread::hardware_concurrency();
    int dataProducerThreadNumber = hardwareConcurrency - 1;
    if (dataProducerThreadNumber < 1) {
        dataProducerThreadNumber = 1;
    }
    qDebug() << "dataProducerThreadNumber" << dataProducerThreadNumber;
    for (int i = 0; i < dataProducerThreadNumber; ++i) {
        QThread* thread = new QThread();
        thread->start();
        m_dataProducerThreads.append(thread);
    }
}
