#ifndef QCLINESERIES_H
#define QCLINESERIES_H

#include <QObject>
#include "QcDataProducer.h"

class QcLineSeries : public QObject
{
    Q_OBJECT
public:
    explicit QcLineSeries(QcDataProducer* dataProducer, QLineSeries* lineSeries, QObject *parent = nullptr);
    ~QcLineSeries();

private slots:
    void updateChart(QList<QPointF> points);

signals:

private:
    QLineSeries* m_lineSeries;
    QcDataProducer* m_dataProducer;

};

#endif // QCLINESERIES_H
