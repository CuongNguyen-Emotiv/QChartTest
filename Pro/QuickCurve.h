#ifndef QUICKCURVE_H
#define QUICKCURVE_H

#include "Controller.h"
#include "QuickQwtPlot.h"
#include "qwt_plot_curve.h"
#include <QQuickItem>

class QuickCurve : public QQuickItem
{
    Q_OBJECT
public:
    explicit QuickCurve(QQuickItem *parent = nullptr);
    ~QuickCurve();

    Q_INVOKABLE void createCurves(int chartNumber, int pointsPerSec);
    Q_INVOKABLE void attach(QVariant plot);

signals:
    void startDataProducer();
    void stopDataProducer();

private slots:
    void updateChart(QList<QVector<double>> xDataList, QList<QVector<double>> yDataList);

private:
    QList<QwtPlotCurve*> m_curves;
    QuickQwtPlot* m_quickQwtPlot = nullptr;
    QThread* m_thread = nullptr;
};

#endif // QUICKCURVE_H
