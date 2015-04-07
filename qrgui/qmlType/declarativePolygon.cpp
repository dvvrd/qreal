#include "declarativePolygon.h"
using namespace qmlTypes;
DeclarativePolygon::DeclarativePolygon(QDeclarativeItem *parent)
	:DeclarativePen(parent)
	, mFill(Qt::black)
	, mX("")
	, mY("")
	, mN(0)
	, mSizex(50)
	, mSizey(50)
{
	// Important, otherwise the paint method is never called
	setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void DeclarativePolygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (mFirstSizex == 0) {
		mFirstSizex = mSizex;
	}
	if (mFirstSizey == 0) {
		mFirstSizey = mSizey;
	}
    painter->fillRect(0, 0, mSizex, mSizey, Qt::transparent);
	QPoint *points = NULL;
    points = getpoints();
	if (points != NULL)
	{
		painter->drawConvexPolygon(points, mN);
		delete[] points;
	}
}
QPoint *DeclarativePolygon::getpoints()
{
	bool mNeedScale = true;
	QPoint *array = new QPoint[mN];
	QStringList xStr = mX.split(",");
	QStringList yStr = mY.split(",");
	float x = 0;
	float y = 0;
	int mStartX = 0;
	int mStartY = 0;
	for (int i = 0; i < mN; i++)
	{
		QString xnum = xStr.at(i);
		if (xnum.endsWith("%"))
		{
			xnum.chop(1);
			x = mSizex * xnum.toFloat() / 100 + mStartX;
		} else if (xnum.endsWith("a") && mNeedScale) {
			xnum.chop(1);
			x = xnum.toFloat() + mStartX;
		} else if (xnum.endsWith("a") && !mNeedScale) {
			xnum.chop(1);
			x = xnum.toFloat() * mSizex / mFirstSizex + mStartX;
		} else {
			x = xnum.toFloat() * mSizex / mFirstSizex + mStartX;
		}

		QString ynum = yStr.at(i);
		if (ynum.endsWith("%"))
		{
			ynum.chop(1);
			y = mSizey * ynum.toFloat() / 100 + mStartY;
		} else if (ynum.endsWith("a") && mNeedScale) {
			ynum.chop(1);
			y = ynum.toFloat() + mStartY;
		} else if (ynum.endsWith("a") && !mNeedScale) {
			ynum.chop(1);
			y = ynum.toFloat() * mSizey / mFirstSizey + mStartY;
		} else
			y = ynum.toFloat() * mSizey / mFirstSizey + mStartY;

		array[i].setX(static_cast<int>(x));
		array[i].setY(static_cast<int>(y));
	}
	return array;
}

QColor DeclarativePolygon::fill() const
{
	return mFill;
}

QString DeclarativePolygon::x() const
{
	return mX;
}

QString DeclarativePolygon::y() const
{
	return mY;
}

int DeclarativePolygon::n() const
{
	return mN;
}

int DeclarativePolygon::sizex() const
{
	return mSizex;
}

int DeclarativePolygon::sizey() const
{
	return mSizey;
}

void DeclarativePolygon::setFill(QColor color)
{
	if (mFill != color) {
		mFill = color;
		updateSize();
		emit fillChanged();
		update();
	}
}

void DeclarativePolygon::setN(int n)
{
	if (mN != n) {
		mN = n;
		updateSize();
		emit nChanged();
		update();
	}
}

void DeclarativePolygon::setX(QString x)
{
	if (mX != x) {
		mX = x;
		updateSize();
		emit xChanged();
		update();
	}
}

void DeclarativePolygon::setY(QString y)
{
	if (mY != y) {
		mY = y;
		updateSize();
		emit yChanged();
		update();
	}
}

void DeclarativePolygon::setSizex(int sizex)
{
	if (mSizex != sizex) {
		mSizex = sizex;
		updateSize();
		emit sizexChanged();
		update();
	}
}

void DeclarativePolygon::setSizey(int sizey)
{
	if (mSizey != sizey) {
		mSizey = sizey;
		updateSize();
		emit sizeyChanged();
		update();
	}
}

void DeclarativePolygon::updateSize()
{
	setX(mX);
	setY(mY);
	setSizex(mSizex);
	setSizey(mSizey);
	setFill(mFill);
	setN(mN);
}
