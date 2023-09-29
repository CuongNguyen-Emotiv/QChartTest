#include "qwt_scale_widget.h"
#include "QuickQwtPlot.h"
#include <QDebug>

QuickQwtPlot::QuickQwtPlot(QQuickItem *parent)  : QQuickPaintedItem(parent)
{
    mPlot = new QwtPlot;

    mPlot->setAttribute(Qt::WA_NoSystemBackground);

    connect(this, SIGNAL(heightChanged()), this, SLOT(heightChanged()));
    connect(this, SIGNAL(widthChanged()), this, SLOT(widthChanged()));

//    mPlot->insertLegend(new QwtLegend(), QwtPlot::BottomLegend);

    // canvas
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setLineWidth(0);
    canvas->setFrameStyle(QFrame::Box | QFrame::Plain);
    canvas->setBorderRadius(0);
#if defined(__APPLE__) || defined (Q_OS_ANDROID) || defined (Q_OS_LINUX)
    canvas->setPaintAttribute(QwtPlotCanvas::BackingStore, false );
#endif
    QPalette canvasPalette(Qt::transparent);
    mPlot->enableAxis(QwtPlot::yLeft,true);
    canvas->setPalette(canvasPalette);
    mPlot->setCanvas(canvas);

    QwtScaleWidget *qwtsw = mPlot->axisWidget(QwtPlot::xBottom);
    QwtScaleWidget *qwtswl = mPlot->axisWidget(QwtPlot::yLeft);
    QPalette palette = qwtsw->palette();
    palette.setColor( QPalette::WindowText, QColor("#E1E1E1"));
    palette.setColor( QPalette::Text, QColor("#747474"));
    qwtsw->setPalette( palette );
    qwtswl->setPalette( palette );
    mPlot->setAxisScale(QwtPlot::xBottom,0,1280);
    mPlot->setAxisScale(QwtPlot::yLeft,0,100);
    mPlot->setAutoReplot(true);
}

void QuickQwtPlot::setSpacing(int baseline, int spacing, bool filter, int start,
                              int pMin, int pMax){
    start=start/100*100;
    if(!filter) {
        mPlot->setAxisScale(QwtPlot::yLeft, start, start + baseline* spacing, spacing);
    } else {
        if (spacing == 0 && baseline > 1) {
            mPlot->setAxisScale(QwtPlot::yLeft, pMin, pMax, spacing);
        } else {
            mPlot->setAxisScale(QwtPlot::yLeft, -spacing/2, (baseline-0.5)* spacing, spacing);
        }
    }
    mPlot->enableAxis(QwtPlot::yLeft,false);
}

void QuickQwtPlot::setAxisScale(int pMin, int pMax){
    mPlot->enableAxis(QwtPlot::yLeft,false);
    mPlot->setAxisScale(QwtPlot::yLeft, pMin, pMax, (pMax-pMin)/10);
    mPlot->enableAxis(QwtPlot::yLeft, mIsAxisesVisible);
}

void QuickQwtPlot::setAutoScale(bool autoScale){
    mPlot->enableAxis(QwtPlot::yLeft,false);
    mPlot->setAxisAutoScale(QwtPlot::yLeft,autoScale);
    mPlot->enableAxis(QwtPlot::yLeft, mIsAxisesVisible);
}

void QuickQwtPlot::setAxisXMaxValue(int maxValue, int point, int range) {
    mPlot->enableAxis(QwtPlot::xBottom,false);
    mPlot->setAxisScaleDraw(QwtPlot::xBottom, new CustomXAxisLabel(maxValue, point, range));
    mPlot->setAxisScale(QwtPlot::xBottom, -1, maxValue, maxValue / point);
    mPlot->enableAxis(QwtPlot::xBottom, mIsAxisesVisible);
}

QuickQwtPlot::~QuickQwtPlot()
{
    delete mPlot;
}

void QuickQwtPlot::paint(QPainter *painter)
{
    mPlot->render(painter);
}

QwtPlot *QuickQwtPlot::getPlot()
{
    return mPlot;
}

QString QuickQwtPlot::titleXBottom() const
{
    return mPlot->axisTitle(QwtPlot::xBottom).text();
}

QString QuickQwtPlot::titleXTop() const
{
    return mPlot->axisTitle(QwtPlot::xTop).text();
}

QString QuickQwtPlot::titleYRight() const
{
    return mPlot->axisTitle(QwtPlot::yRight).text();
}

QString QuickQwtPlot::titleYLeft() const
{
    return mPlot->axisTitle(QwtPlot::yLeft).text();
}

void QuickQwtPlot::heightChanged()
{
    mPlot->setFixedHeight(contentsBoundingRect().height());
}

void QuickQwtPlot::widthChanged()
{
    mPlot->setFixedWidth(contentsBoundingRect().width());
}

void QuickQwtPlot::setAxisXBottom(QString arg)
{
    mPlot->setAxisTitle(QwtPlot::xBottom, arg);
}

void QuickQwtPlot::setAxisXTop(QString arg)
{
    mPlot->setAxisTitle(QwtPlot::xTop, arg);
}

void QuickQwtPlot::setAxisYRight(QString arg)
{
    mPlot->setAxisTitle(QwtPlot::yRight, arg);
}

void QuickQwtPlot::setAxisYLeft(QString arg)
{
    mPlot->setAxisTitle(QwtPlot::yLeft, arg);
}

QString QuickQwtPlot::title() const
{
    return mPlot->title().text();
}

void QuickQwtPlot::setTitle(QString arg)
{
    mPlot->setTitle(arg);
}

void QuickQwtPlot::setBorderRadius(int radius)
{
    static_cast<QwtPlotCanvas *>(mPlot->canvas())->setBorderRadius(radius);
}

void QuickQwtPlot::disableBackingStore()
{
    static_cast<QwtPlotCanvas *>(mPlot->canvas())->setPaintAttribute(QwtPlotCanvas::BackingStore, false);
}

int QuickQwtPlot::canvasWidth() const
{
    return mPlot->canvas()->width();
}

int QuickQwtPlot::canvasX() const
{
    return mPlot->canvas()->x();
}

int QuickQwtPlot::getPMax(){
    return mPlot->axisScaleDiv(QwtPlot::yLeft).upperBound();
}

bool QuickQwtPlot::isAxisesVisible() const
{
    return mIsAxisesVisible;
}

void QuickQwtPlot::setIsAxisesVisible(bool showAxises)
{
    if (mIsAxisesVisible != showAxises) {
        mIsAxisesVisible = showAxises;
        mPlot->enableAxis(0,mIsAxisesVisible);
        mPlot->enableAxis(1,mIsAxisesVisible);
        mPlot->enableAxis(2,mIsAxisesVisible);
        mPlot->enableAxis(3,mIsAxisesVisible);
    }
}

int QuickQwtPlot::getPMin(){
    return mPlot->axisScaleDiv(QwtPlot::yLeft).lowerBound();
}
