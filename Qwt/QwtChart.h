#ifndef QWTCHART_H
#define QWTCHART_H

#include <QQuickPaintedItem>
#include <QQuickItem>

#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_symbol.h"
#include "qwt_plot_renderer.h"

class QwtChart : public QQuickPaintedItem
{
public:
    QwtChart(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;

    QwtPlot* qwtPlot();
private:
    QwtPlot m_plot;
};

#endif // QWTCHART_H
