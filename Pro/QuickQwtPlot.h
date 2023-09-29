#ifndef QUICKWIDGET_H
#define QUICKWIDGET_H

#if defined(_WIN32) || defined(_WIN64)
#include <qwt_legend.h>
#include <qwt_plot_canvas.h>
#include "qwt_plot.h"
#include <qwt_text.h>
#else
#include "qwt_legend.h"
#include "qwt_plot_canvas.h"
#include "qwt_plot.h"
#include "qwt_text.h"
#endif

#include <QQuickPaintedItem>
#include <qwt_scale_draw.h>

class QwtPlot;

class CustomXAxisLabel: public QwtScaleDraw
{
    public:
    int mMaxValue = 0;
    int mPoint = 1;
    int mRange = 1;

    CustomXAxisLabel(int maxValue, int point, int range)
    {
        mMaxValue = maxValue;
        mPoint = point;
        mRange = range;
    }
    virtual QwtText label(double v) const
    {
        int step = mMaxValue / mPoint;
        for(int i = 0; i <= mPoint; i++) {
            if(v == i * step) {
                return QString::number(i * mRange / mPoint);
            }
        }
        return QString("0");
    }
};

class QuickQwtPlot : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString titleYLeft   READ titleYLeft   WRITE setAxisYLeft)
    Q_PROPERTY(QString titleYRight  READ titleYRight  WRITE setAxisYRight)
    Q_PROPERTY(QString titleXBottom READ titleXBottom WRITE setAxisXBottom)
    Q_PROPERTY(QString titleXTop    READ titleXTop    WRITE setAxisXTop)
    Q_PROPERTY(QString title        READ title        WRITE setTitle)
    Q_PROPERTY(bool isAxisesVisible READ isAxisesVisible WRITE setIsAxisesVisible)

public:
    QuickQwtPlot(QQuickItem *parent = 0);
    ~QuickQwtPlot();

    void paint(QPainter *painter);

    QwtPlot *getPlot();

    QString titleXBottom() const;
    QString titleXTop() const;
    QString titleYRight() const;
    QString titleYLeft() const;
    QString title() const;

    void setSpacing(int baseline, int spacing, bool filter, int start,
                    int pMin = -100, int pMax = 100);
    void setAxisScale(int pMin, int pMax);
    void setAutoScale(bool autoScale);
    void setAxisXMaxValue(int maxValue, int point = 10, int range = 10);

    int  getPMin();
    int  getPMax();

    bool isAxisesVisible() const;
    void setIsAxisesVisible(bool showAxises);

    float penWidth = 1;
public slots:
    void heightChanged();
    void widthChanged();
    void setAxisXBottom(QString arg);
    void setAxisXTop(QString arg);
    void setAxisYRight(QString arg);
    void setAxisYLeft(QString arg);
    void setTitle(QString arg);

    void setBorderRadius(int radius);
    void disableBackingStore();

    int canvasWidth() const;
    int canvasX() const;

private:
    QwtPlot *mPlot;
    bool mIsAxisesVisible = true;
};

#endif // QUICKWIDGET_H
