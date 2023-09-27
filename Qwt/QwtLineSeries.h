#ifndef QWTLINESERIES_H
#define QWTLINESERIES_H

#include <QObject>
#include "qwt_plot_curve.h"
#include "QwtDataProducer.h"

class QwtLineSeries : public QObject
{
    Q_OBJECT
public:
    explicit QwtLineSeries(QwtPlotCurve* curve, QwtDataProducer* dataProducer, QObject *parent = nullptr);

signals:

private:
    QwtPlotCurve* m_curve;
};

#endif // QWTLINESERIES_H
