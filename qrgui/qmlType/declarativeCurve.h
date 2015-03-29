#pragma once

#include <QtDeclarative/QDeclarativeItem>

#include "declarativePen.h"

namespace qmlTypes {

class DeclarativeCurve : public DeclarativePen
{
	Q_OBJECT

	Q_PROPERTY(int startx READ startx WRITE setStartx NOTIFY startxChanged)
	Q_PROPERTY(int starty READ starty WRITE setStarty NOTIFY startyChanged)
	Q_PROPERTY(int endx READ endx WRITE setEndx NOTIFY endxChanged)
	Q_PROPERTY(int endy READ endy WRITE setEndy NOTIFY endyChanged)
	Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
	Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
	Q_PROPERTY(int sizex READ sizex WRITE setSizex NOTIFY sizexChanged)
	Q_PROPERTY(int sizey READ sizey WRITE setSizey NOTIFY sizeyChanged)
	Q_PROPERTY(QColor fill READ fill WRITE setFill NOTIFY fillChanged)

public:
	DeclarativeCurve(QDeclarativeItem *parent = 0);
	/// Returns x coordinate of the starting point
	int startx() const;
	/// Returns y coordinate of the starting point
	int starty() const;
	/// Returns x coordinate of the ending point
	int endx() const;
	/// Returns y coordinate of the ending point
	int endy() const;
	/// Returns x coordinate of the middle point
	int x() const;
	/// Returns y coordinate of the middle point
	int y() const;
	/// Returns width of background
	int sizex() const;
	/// Returns height of background
	int sizey() const;
	/// Returns color
	QColor fill() const;

signals:
	/// Signal change of x coordinate of the starting point
	void startxChanged();
	/// Signal change of y coordinate of the starting point
	void startyChanged();
	/// Signal change of x coordinate of the ending point
	void endxChanged();
	/// Signal change of y coordinate of the ending point
	void endyChanged();
	/// Signal change of x coordinate of the middle point
	void xChanged();
	/// Signal change of y coordinate of the middle point
	void yChanged();
	/// Signal change width of background
	void sizexChanged();
	/// Signal change height of background
	void sizeyChanged();
	/// Signal change color
	void fillChanged();

protected:
	void updateSize();
	/// Set x coordinate of the starting point
	void setStartx(int startx);
	/// Set y coordinate of the starting point
	void setStarty(int starty);
	/// Set x coordinate of the ending point
	void setEndx(int endx);
	/// Set y coordinate of the ending point
	void setEndy(int endy);
	/// Set x coordinate of the middle point
	void setX(int x);
	/// Set y coordinate of the middle point
	void setY(int y);
	/// Set width of background
	void setSizex(int sizex);
	/// Set height of background
	void setSizey(int sizey);
	/// Set color
	void setFill(QColor color);

private:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
	int mStartx;
	int mStarty;
	int mEndx;
	int mEndy;
	int mX;
	int mY;
	int mSizex;
	int mSizey;
	int mFirstSizex;
	int mFirstSizey;
	QColor mFill;
};

}
QML_DECLARE_TYPE(qmlTypes::DeclarativeCurve)
