#include "QcustomPlotItem.h"

QcustomPlotItem::QcustomPlotItem(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    m_plot.setTitle("Line Chart");
    m_plot.setCanvasBackground(Qt::white);
    m_plot.setAutoReplot();

    QwtPlotCurve *curve = new QwtPlotCurve("Line");
    curve->setPen(Qt::black);
    curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    QVector<double> x(10), y(10);
    for (int i = 0; i < 10; i++) {
        x[i] = i;
        y[i] = i;
    }
    curve->setSamples(x, y);
    curve->attach(&m_plot);
}

void QcustomPlotItem::paint(QPainter *painter)
{
    QRectF rect = boundingRect();
    m_plot.setGeometry(rect.toRect());

    QwtPlotRenderer renderer;
    renderer.render(&m_plot, painter, rect.toRect());
}
