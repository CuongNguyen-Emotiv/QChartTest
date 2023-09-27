#include "QwtLineSeries.h"

QwtLineSeries::QwtLineSeries(QwtPlotCurve *curve, QwtDataProducer *dataProducer, QObject *parent)
    : QObject{parent}
{
    m_curve = curve;
}
