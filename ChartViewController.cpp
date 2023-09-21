#include "ChartViewController.h"
#include <QValueAxis>

ChartViewController::~ChartViewController()
{
    emit stopDataProducer();
    if (m_dataProducerThread) {
        m_dataProducerThread->quit();
        m_dataProducerThread->wait();
    }
    delete m_dataProducerThread;
}

ChartViewController *ChartViewController::instance()
{
    static ChartViewController chartViewController;
    return &chartViewController;
}

void ChartViewController::setChartViews(QList<QQuickItem *> chartViews)
{
    //clean up
    for (auto& oldChartView : m_chartViews) {
        if (oldChartView) {
            delete oldChartView;
        }
    }
    m_chartViews.clear();

    for (auto& dataProducer : m_dataProducers) {
        if (dataProducer) {
            delete dataProducer;
        }
    }
    m_dataProducers.clear();

    //create new
    for (int i = 0; i < chartViews.size(); ++i) {
        ChartViewCpp* chartView = new ChartViewCpp(this);
        chartView->setChartView(chartViews[i]);
        m_chartViews.append(chartView);
    }

    for (int i = 0; i < chartViews.size(); ++i) {
        DataProducer* dataProducer = new DataProducer();
        connect(this, &ChartViewController::startDataProducer, dataProducer, &DataProducer::start);
        connect(this, &ChartViewController::stopDataProducer, dataProducer, &DataProducer::stop);
        connect(dataProducer, &DataProducer::updateChart, m_chartViews[i], &ChartViewCpp::updateChart);
        dataProducer->moveToThread(m_dataProducerThread);
        m_dataProducers.append(dataProducer);
    }
    emit startDataProducer();
}

void ChartViewController::setPointsPerSec(int pointsPerSec)
{
    for (auto& dataProducer : m_dataProducers) {
        dataProducer->setPointsPerSec(pointsPerSec);
    }
    for (auto& chartView : m_chartViews) {
        chartView->setPointsPerSec(pointsPerSec);
    }
}

ChartViewController::ChartViewController(QObject *parent)
    : QObject{parent}
{
    m_dataProducerThread = new QThread(this);
    m_dataProducerThread->start();
}
