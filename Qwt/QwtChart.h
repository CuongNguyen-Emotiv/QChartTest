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
    Q_OBJECT
    Q_PROPERTY(int curveNumber READ curveNumber WRITE setCurveNumber NOTIFY curveNumberChanged FINAL)
public:
    QwtChart(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;

    QwtPlot* plot();
    int curveNumber() const;
    void setCurveNumber(int newCurveNumber);

signals:
    void curveNumberChanged();

private:
    QwtPlot m_plot;

    int m_curveNumber = 0;
};

#endif // QWTCHART_H
