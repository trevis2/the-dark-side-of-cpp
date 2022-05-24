#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H
#include <QStylePainter>
#include <QStyleOptionSlider>
#include <QStyleOptionComplex>
#include <QSlider>
#include <QColor>
#include "math.h"

class CustomSlider:public QSlider
{
public:
    explicit CustomSlider(Qt::Orientation orientation, QWidget *parent = nullptr):QSlider(orientation, parent){};
    explicit CustomSlider(QWidget *parent = nullptr):QSlider(parent){
        this->setStyleSheet("\
                            QSlider::groove:horizontal {\
                                height: 8px; \
                                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\
                                margin: 2px 0;\
                            }\
                            \
                            QSlider::handle:horizontal {\
                                background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\
                                border: 1px solid #5c5c5c;\
                                width: 18px;\
                                margin: -2px 0; \
                                border-radius: 3px;\
                            }\
                        ");
    };
protected:
    virtual void paintEvent(QPaintEvent *ev)
    {
        QStylePainter p(this);
        QStyleOptionSlider opt;
        initStyleOption(&opt);

        QRect handle = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

        int interval = tickInterval();
        if (interval == 0)
        {
            interval = pageStep();
        }

        if (tickPosition() != NoTicks)
        {
            for (int i = minimum(); i <= maximum(); i += interval)
            {
                int x = std::round((double)((double)((double)(i - this->minimum()) / (double)(this->maximum() - this->minimum())) * (double)(this->width() - handle.width()) + (double)(handle.width() / 2.0))) - 1;
                int h = 4;
                p.setPen(QColor("#a5a294"));
                if (tickPosition() == TicksBothSides || tickPosition() == TicksAbove)
                {
                    int y = this->rect().top();
                    p.drawLine(x, y, x, y + h);
                }
                if (tickPosition() == TicksBothSides || tickPosition() == TicksBelow)
                {
                    int y = this->rect().bottom();
                    p.drawLine(x, y, x, y - h);
                }
            }
        }

        QSlider::paintEvent(ev);
    }
};
#endif // CUSTOMSLIDER_H
