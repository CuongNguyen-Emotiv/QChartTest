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
    for (auto& oldChartView : m_chartViews) {
        if (oldChartView) {
            delete oldChartView;
        }
    }
    m_chartViews.clear();
    for (int i = 0; i < chartViews.size(); ++i) {
        ChartViewCpp* chartView = new ChartViewCpp(this);
        chartView->setChartView(chartViews[i]);
        m_chartViews.append(chartView);
    }
    emit startDataProducer();
}

void ChartViewController::setPointsPerSec(int pointsPerSec)
{
    m_dataProducer.setPointsPerSec(pointsPerSec);
    for (auto& chartView : m_chartViews) {
        chartView->setPointsPerSec(pointsPerSec);
    }
}

void ChartViewController::addDataPoint(double x, double y)
{
    for (const auto& chartView : m_chartViews) {
        chartView->addDataPoint(x, y);
    }
}

void ChartViewController::updateChartView()
{
    for (const auto& chartView : m_chartViews) {
        chartView->updateChartView();
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
