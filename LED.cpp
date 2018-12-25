/*
 * LED.cpp
 *
 *  Created on: 30.11.2018
 *      Author: wenzel
 */

#include "LED.h"

LED::LED(QWidget *parent) : QWidget(parent)
{
    setFixedSize(28, 28);
    lit = false;
    ledOnColor    = Qt::green;
    ledOffColor   = Qt::red;
    ledOnPattern  = Qt::SolidPattern;
    ledOffPattern = Qt::SolidPattern;
    ledSize=20;

}

LED::~LED() {
	// TODO Auto-generated destructor stub
}

void LED::setLedSize(int size)
{
    ledSize=size;
    setFixedSize(size+10, size+10);
    repaint();
}

void LED::setState(bool _state)
{
	lit = _state;
	repaint();
}

void LED::setRed()
{
	lit = false;
	repaint();
}

void LED::setGreen()
{
	lit = true;
	repaint();
}

void LED::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	lit ?  p.setBrush(QBrush(ledOnColor, ledOnPattern)) : p.setBrush(QBrush(ledOffColor, ledOffPattern));
	p.drawEllipse(0,0,ledSize,ledSize);
}

void LED::mousePressEvent(QMouseEvent *e)
{
	Q_UNUSED(e);
	emit clicked();
}
