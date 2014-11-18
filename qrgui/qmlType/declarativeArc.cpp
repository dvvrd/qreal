#include "declarativeArc.h"

#include <QtGui/QPainter>

using namespace qmlTypes;

DeclarativeArc::DeclarativeArc(QDeclarativeItem *parent)
	: DeclarativePen(parent)
	, mX1(0)
	, mY1(0)
	, mX2(0)
	, mY2(0)
	, mStartAngle(0)
	, mSpanAngle(0)
{
	// Important, otherwise the paint method is never called
	setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void DeclarativeArc::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget)
{
	int width, height;
	QPen pen(mColor, mWidth);
	if (mStyle == "solid") {
		pen.setStyle(Qt::SolidLine);
	} else if (mStyle == "dot") {
		pen.setStyle(Qt::DotLine);
	} else if (mStyle == "dash") {
		pen.setStyle(Qt::DashLine);
	} else if (mStyle == "dashdot") {
		pen.setStyle(Qt::DashDotLine);
	} else if (mStyle == "dashdotdot") {
		pen.setStyle(Qt::DashDotDotLine);
	} else if (mStyle == "none") {
		pen.setStyle(Qt::NoPen);
	}

	painter->setPen(pen);
	if (smooth()) {
		painter->setRenderHint(QPainter::Antialiasing, true);
	}
	width = abs(mX2 - mX1);
	height = abs(mY2 - mY1);

	painter->drawArc(mX1, mY1, width, height, mStartAngle, mSpanAngle);
}

int DeclarativeArc::x1() const
{
	return mX1;
}

int DeclarativeArc::y1() const
{
	return mY1;
}

int DeclarativeArc::x2() const
{
	return mX2;
}

int DeclarativeArc::y2() const
{
	return mY2;
}

int DeclarativeArc::startAngle() const
{
	return mStartAngle;
}

int DeclarativeArc::spanAngle() const
{
	return mSpanAngle;
}

void DeclarativeArc::setX1(int x1)
{
	if (mX1 != x1) {
		mX1 = x1;
		updateSize();
		emit x1Changed();
		update();
	}
}

void DeclarativeArc::setY1(int y1)
{
	if (mY1 != y1) {
		mY1 = y1;
		updateSize();
		emit y1Changed();
		update();
	}
}

void DeclarativeArc::setX2(int X2)
{
	if (mX2 != X2) {
		mX2 = X2;
		updateSize();
		emit x2Changed();
		update();
	}
}

void DeclarativeArc::setY2(int Y2)
{
	if (mY2 != Y2) {
		mY2 = Y2;
		updateSize();
		emit y2Changed();
		update();
	}
}

void DeclarativeArc::setStartAngle(int startAngle)
{
	if (mStartAngle != startAngle) {
		mStartAngle = startAngle;
		updateSize();
		emit startAngleChanged();
		update();
	}
}

void DeclarativeArc::setSpanAngle(int spanAngle)
{
	if (mSpanAngle != spanAngle) {
		mSpanAngle = spanAngle;
		updateSize();
		emit spanAngleChanged();
		update();
	}
}

void DeclarativeArc::updateSize() {
	setX1(mX1);
	setY1(mY1);
	setX2(mX2);
	setY2(mY2);
	setStartAngle(mStartAngle);
	setSpanAngle(mSpanAngle);
}
