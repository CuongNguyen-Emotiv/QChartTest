#include "QuickCurve.h"
#include "ProDataProceducer.h"
#include "QtGui/qpen.h"
#include "QuickQwtPlot.h"

QuickCurve::QuickCurve(QQuickItem *parent)
    : QQuickItem{parent}
{
    m_thread = new QThread();
    m_thread->start();
}

QuickCurve::~QuickCurve()
{
    if (m_thread) {
        m_thread->quit();
        m_thread->wait();
        delete m_thread;
    }
}

void QuickCurve::createCurves(int chartNumber, int pointsPerSec)
{
    if (chartNumber <= 0) {
        return;
    }
    for (auto& curve : m_curves) {
        curve->detach();
    }
    m_curves.clear();

    for (int i = 0; i < chartNumber; i++) {
        QwtPlotCurve* curve = new QwtPlotCurve();
        curve->setRenderHint(QwtPlotItem::RenderAntialiased);
        curve->setPen(QPen(Qt::red));
        curve->setStyle(QwtPlotCurve::Lines);
        curve->setCurveAttribute(QwtPlotCurve::Fitted, true);
        m_curves.append(curve);
    }

    ProDataProceducer* dataProducer = new ProDataProceducer(chartNumber, pointsPerSec);
    dataProducer->moveToThread(m_thread);

    connect(this, &QuickCurve::startDataProducer, dataProducer, &ProDataProceducer::start);
    connect(this, &QuickCurve::stopDataProducer, dataProducer, &ProDataProceducer::stop);
    connect(this, &QuickCurve::stopDataProducer, dataProducer, &ProDataProceducer::deleteLater);
    connect(dataProducer, &ProDataProceducer::updateChart, this, &QuickCurve::updateChart);
}

void QuickCurve::attach(QVariant plot)
{
    if(plot.canConvert<QuickQwtPlot*>()) {
        m_quickQwtPlot = plot.value<QuickQwtPlot*>();
        for (auto& curve : m_curves) {
            curve->attach(m_quickQwtPlot->getPlot());
        }
    }

    emit startDataProducer();
}

void QuickCurve::updateChart(QList<QVector<double> > xDataList, QList<QVector<double> > yDataList)
{
    if (m_quickQwtPlot) {
        for (int i = 0; i < m_curves.size(); i++) {
            m_curves[i]->setSamples(xDataList[i], yDataList[i]);
        }
        m_quickQwtPlot->update();
    }
}
