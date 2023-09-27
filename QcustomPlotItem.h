#ifndef QCUSTOMPLOTITEM_H
#define QCUSTOMPLOTITEM_H

#include <QQuickPaintedItem>
#include <QQuickItem>

#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_symbol.h"
#include "qwt_plot_renderer.h"

class QcustomPlotItem : public QQuickPaintedItem
{
public:
    QcustomPlotItem(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;

private:
    QwtPlot m_plot;
};

#endif // QCUSTOMPLOTITEM_H
