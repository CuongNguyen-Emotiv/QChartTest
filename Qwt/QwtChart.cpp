#include "QwtChart.h"
#include "Constant.h"

QwtChart::QwtChart(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    m_plot.setTitle("");
    m_plot.setCanvasBackground(Qt::white);
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

QwtPlot *QwtChart::plot()
{
    return &m_plot;
}

int QwtChart::curveNumber() const
{
    return m_curveNumber;
}

void QwtChart::setCurveNumber(int newCurveNumber)
{
    if (newCurveNumber > 0) {
        m_plot.setAxisScale(QwtPlot::yLeft, 0, newCurveNumber * CHART_RANGE);
    }
    if (m_curveNumber != newCurveNumber) {
        m_curveNumber = newCurveNumber;
        emit curveNumberChanged();
    }
}
