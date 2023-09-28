#include "QwtChart.h"

QwtChart::QwtChart(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    m_plot.setTitle("");
    m_plot.setCanvasBackground(Qt::white);
    m_plot.setAutoReplot();
    m_plot.setAxisVisible(QwtPlot::xBottom, false);
    m_plot.setAxisVisible(QwtPlot::yLeft, false);
}

void QwtChart::paint(QPainter *painter)
{
    QRectF rect = boundingRect();
    m_plot.setGeometry(rect.toRect());

    QwtPlotRenderer renderer;
    renderer.render(&m_plot, painter, rect.toRect());
}

QwtPlot *QwtChart::qwtPlot()
{
    return &m_plot;
}
