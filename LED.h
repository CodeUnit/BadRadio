/*
 * LED.h
 *
 *  Created on: 30.11.2018
 *      Author: wenzel
 */

#ifndef LED_H_
#define LED_H_

#include <QWidget>
#include <QPainter>
#include <QApplication>
#include <QTextStream>

class LED: public QWidget {

	Q_OBJECT

public:
	LED(QWidget *parent = 0);
	virtual ~LED();
	void setLedSize(int size);
	void setState(bool _state);
	void setRed();
	void setGreen();

private:
  bool lit;
  QColor ledOnColor;
  QColor ledOffColor;
  Qt::BrushStyle ledOnPattern;
  Qt::BrushStyle ledOffPattern;
  int ledSize;

protected:
   void paintEvent(QPaintEvent *);
   void mousePressEvent(QMouseEvent *e);

signals:
	void clicked();


};

#endif /* LED_H_ */
