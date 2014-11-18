#include "declarativePath.h"

using namespace qmlTypes;

DeclarativePath::DeclarativePath(QDeclarativeItem *parent)
	: DeclarativePen(parent)
	, mStr("")
	, mSizex(0)
	, mSizey(0)
	, mFirstSizex(0)
	, mFirstSizey(0)
	, mFill(Qt::transparent)
{
	// Important, otherwise the paint method is never called
	setFlag(QGraphicsItem::ItemHasNoContents, false);
}

bool DeclarativePath::isNotLCMZ(QString str, int i)
{
	return (i != str.length()) && (str[i] != 'L') && (str[i] != 'C') && (str[i] != 'M')
		&& (str[i] != 'Z');
}

void DeclarativePath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

	if (mFirstSizex == 0) {
		mFirstSizex = mSizex;
	}
	if (mFirstSizey == 0) {
		mFirstSizey = mSizey;
	}
	QString s1;
	QPointF end_point;
	QPointF c1;
	QPointF c2;
	QPainterPath path;
	int mStartX = 0;
	int mStartY = 0;
	painter->fillRect(0, 0, mSizex, mSizey, mFill);
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
	//painter->setPen(pen);

	QString d_cont = mStr;
	d_cont.append(" Z");
	for (int i = 0; i < d_cont.length() - 1;)
	{
		int j = 0;
		if (d_cont[i] == 'M')
		{
			j = i + 2;
			while (isNotLCMZ(d_cont, j))
			{
				while (d_cont[j] != ' ')
				{
					s1.append(d_cont[j]);
					++j;
				}
				end_point.setX(s1.toFloat() * mSizex / mFirstSizex + mStartX);
				s1.clear();
				++j;
				while (d_cont[j] != ' ')
				{
					s1.append(d_cont[j]);
					++j;
				}
				end_point.setY(s1.toFloat() * mSizey / mFirstSizey + mStartY);
				++j;
				s1.clear();
			}

			path.moveTo(end_point);
			i = j;
		}
		else if (d_cont[i] == 'L')
		{
			j = i + 2;
			while (isNotLCMZ(d_cont, j))
			{
				while (d_cont[j] != ' ')
				{
					s1.append(d_cont[j]);
					++j;
				}

				end_point.setX(s1.toFloat() * mSizex / mFirstSizex + mStartX);
				s1.clear();
				++j;

				while (d_cont[j] != ' ')
				{
					s1.append(d_cont[j]);
					++j;
				}
				end_point.setY(s1.toFloat() * mSizey / mFirstSizey + mStartY);
				++j;
				s1.clear();
			}

			path.lineTo(end_point);
			i = j;
		}
		else if (d_cont[i] == 'C')
		{
			j = i + 2;
			while(isNotLCMZ(d_cont, j))
			{
				while (!(d_cont[j] == ' '))
				{
					s1.append(d_cont[j]);
					++j;
				}

				c1.setX(s1.toFloat() * mSizex / mFirstSizex + mStartX);
				s1.clear();
				++j;

				while (d_cont[j] != ' ')
				{
					s1.append(d_cont[j]);
					++j;
				}

				c1.setY(s1.toFloat() * mSizey / mFirstSizey + mStartY);
				s1.clear();
				++j;

				while (d_cont[j] != ' ')
				{
					s1.append(d_cont[j]);
					++j;
				}

				c2.setX(s1.toFloat() * mSizex / mFirstSizex + mStartX);
				s1.clear();
				++j;

				while (d_cont[j] != ' ')
				{
					s1.append(d_cont[j]);
					++j;
				}

				c2.setY(s1.toFloat() * mSizey / mFirstSizey + mStartY);
				s1.clear();
				++j;

				while (d_cont[j] != ' ')
				{
					s1.append(d_cont[j]);
					++j;
				}

				end_point.setX(s1.toFloat() * mSizex / mFirstSizex + mStartX);
				s1.clear();
				++j;

				while (d_cont[j] != ' ')
				{
					s1.append(d_cont[j]);
					++j;
				}

				end_point.setY(s1.toFloat() * mSizey / mFirstSizey + mStartY);
				s1.clear();
				++j;
			}

			path.cubicTo(c1, c2, end_point);
			i = j;

		} else if (d_cont[i] == 'Z')
		{
			path.closeSubpath();
		}
	}
	painter->drawPath(path);
}

QString DeclarativePath::str() const
{
	return mStr;
}

QColor DeclarativePath::fill() const
{
	return mFill;
}

int DeclarativePath::sizex() const
{
	return mSizex;
}

int DeclarativePath::sizey() const
{
	return mSizey;
}

void DeclarativePath::setStr(QString str)
{
	if (mStr != str)
	{
		mStr = str.remove(0, 1);
		updateSize();
		emit strChanged();
		update();
	}
}

void DeclarativePath::setFill(QColor color)
{
	if (mFill != color)
	{
		mFill = color;
		updateSize();
		emit fillChanged();
		update();
	}
}

void DeclarativePath::setSizex(int sizex)
{
	if (mSizex != sizex) {
		mSizex = sizex;
		updateSize();
		emit sizexChanged();
		update();
	}
}

void DeclarativePath::setSizey(int sizey)
{
	if (mSizey != sizey) {
		mSizey = sizey;
		updateSize();
		emit sizeyChanged();
		update();
	}
}

void DeclarativePath::updateSize()
{
	setStr(mStr);
	setFill(mFill);
	setSizex(mSizex);
	setSizey(mSizey);
}
