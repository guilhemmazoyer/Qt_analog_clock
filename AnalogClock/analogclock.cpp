#include "analogclock.h"

#include <QPainter>
#include <QTime>
#include <QTimer>

AnalogClock::AnalogClock(QWidget *parent) : QWidget(parent){
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));
    timer->start(1000);

    setWindowTitle(tr("Analog Clock"));
    resize(200, 200);
}
void AnalogClock::paintEvent(QPaintEvent *){
    static const QPoint hourHand[3] = {
        QPoint(5, 6),
        QPoint(-5, 6),
        QPoint(-5, -50)
    };

    static const QPoint minuteHand[3] = {
        QPoint(5, 6),
        QPoint(-5, 6),
        QPoint(0, -70)
    };

    static const QPoint secondHandYellowCover[17] = {
        QPoint(0, 0),
        QPoint(2.9, 0.18),
        QPoint(4.54, -0.91),
        QPoint(4.9, -22.14),
        QPoint(8.53, -26.31),
        QPoint(14.33, -32.66),
        QPoint(8.17, -45),
        QPoint(20.32, -58.06),
        QPoint(0, -89.27),
        QPoint(-13.61, -73.31),
        QPoint(0.54, -55.34),
        QPoint(-7.08, -46.27),
        QPoint(0, -36.29),
        QPoint(-1.45, -34.29),
        QPoint(-6.53, -28.13),
        QPoint(-3.99, -1.63),
        QPoint(-2.72, -0.18)
    };

    static const QPoint secondHandBrownCover[16] = {
        QPoint(0, 0),
        QPoint(2.9, 0.18),
        QPoint(4.54, -0.91),
        QPoint(4.9, -22.14),
        QPoint(8.53, -26.31),
        QPoint(8.53, -28.67),
        QPoint(5.81, -27.94),
        QPoint(5.81, -30.67),
        QPoint(2.72, -30.12),
        QPoint(2.72, -32.84),
        QPoint(0, -32.3),
        QPoint(0, -34.48),
        QPoint(-1.45, -34.29),
        QPoint(-6.53, -28.13),
        QPoint(-3.99, -1.63),
        QPoint(-2.72, -0.18)
    };

    QColor yellowSecondColor(226, 215, 73);
    QColor brownSecondColor(120, 69, 48);
    QColor minuteColor(0, 127, 127, 200);
    QColor hourColor(127, 0, 127, 200);
    QColor black(0, 0, 0);
    QColor white(255, 255, 255);
    QColor red(255, 25, 25);

    int side = qMin(width(), height());
    QTime time = QTime::currentTime();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    // Cadrant
    painter.setPen(black);
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }
    painter.restore();
    
    painter.setPen(red);
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }
    painter.restore();

    // Secondes - yellow / brown
    painter.setPen(Qt::SolidLine);
    painter.setPen(Qt::RoundJoin);
    painter.setPen(black);

    painter.save();
    painter.rotate(time.second()*(360/60.0));
    painter.setBrush(yellowSecondColor);
    painter.drawConvexPolygon(secondHandYellowCover, 17);

    painter.setBrush(brownSecondColor);
    painter.drawConvexPolygon(secondHandBrownCover, 16);
    painter.restore();

    // Minutes
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    // Heures
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);

    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    // Pokeball
        // Point central
    painter.setPen(Qt::NoPen);
    int static sizeCentral = 20;

    painter.save();
    painter.translate(-sizeCentral/2,-sizeCentral/2);
    painter.setBrush(black);
    painter.drawEllipse(0, 0, sizeCentral, sizeCentral);
    painter.restore();

        // Moitie haute
    painter.setPen(Qt::NoPen);
    painter.setBrush(red);
    QRectF redRectangle(-9, -9, 18, 18);
    int startAngle = 0 * 16;
    int spanAngle = 180 * 16;
    painter.drawPie(redRectangle, startAngle, spanAngle);

        // Moitie basse
    painter.setPen(Qt::NoPen);
    painter.setBrush(white);
    QRectF whiteRectangle(-9, -9, 18, 18);
    startAngle = 0 * 16;
    spanAngle = -180 * 16;
    painter.drawPie(whiteRectangle, startAngle, spanAngle);

        // Trait noir horizontal
    painter.setPen(Qt::NoPen);
    painter.setBrush(black);
    QRectF blackRectangle(-9.5, -0.65, 19, 1.3);
    painter.drawRect(blackRectangle);

        // Partie noire centrale
    painter.setPen(Qt::NoPen);
    int static sizeLittleCentral = 8;

    painter.save();
    painter.translate(-sizeLittleCentral/2,-sizeLittleCentral/2);
    painter.setBrush(black);
    painter.drawEllipse(0, 0, sizeLittleCentral, sizeLittleCentral);
    painter.restore();

        // Partie blanche centrale
    painter.setPen(Qt::NoPen);
    double sizeLittleButtonCentral = 2.8;
    qreal test = sizeLittleButtonCentral;

    painter.save();
    painter.setBrush(white);
    static const QPointF littleBlackPoint = QPoint(0, 0);
    painter.drawEllipse(littleBlackPoint, test, test);
    painter.restore();
}

