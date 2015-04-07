#pragma once

#include "declarativePen.h"

#include <QtDeclarative/QDeclarativeItem>

namespace qmlTypes {

class DeclarativePolygon : public DeclarativePen
{
	Q_OBJECT

	Q_PROPERTY(int n READ n WRITE setN NOTIFY nChanged)
	Q_PROPERTY(QString x READ x WRITE setX NOTIFY xChanged)
	Q_PROPERTY(QString y READ y WRITE setY NOTIFY yChanged)
	Q_PROPERTY(QColor fill READ fill WRITE setFill NOTIFY fillChanged)
	Q_PROPERTY(int sizex READ sizex WRITE setSizex NOTIFY sizexChanged)
	Q_PROPERTY(int sizey READ sizey WRITE setSizey NOTIFY sizeyChanged)

public:
	explicit DeclarativePolygon(QDeclarativeItem *parent = 0);

	/// Returns size of the array of points
	int n() const;
	/// Returns width of background
	int sizex() const;
	/// Returns height of background
	int sizey() const;
	/// Returns the color of Polygon
	QColor fill() const;
	/// Returns array of x coordinates
	QString x() const;
	/// Returns array of y coordinates
	QString y() const;

signals:
	/// Signal change color
	void fillChanged();
	/// Signal change array of x coordinates
	void xChanged();
	/// Signal change array of y coordinates
	void yChanged();
	/// Signal change width of background
	void sizexChanged();
	/// Signal change height of background
	void sizeyChanged();
	/// Signal change of the array of points
	void nChanged();

protected:
	/// Set array of x coordinates
	void setX(QString x);
	/// Set array of y coordinates
	void setY(QString y);
	/// Set width of background
	void setSizex(int sizex);
	/// Set height of background
	void setSizey(int sizey);
	/// Set color
	void setFill(QColor color);
	/// Set size of the array of points
	void setN(int n);
	void updateSize();

private:
	void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget);
	QPoint *getpoints();

public:
	QColor mFill;
	QString mX;
	QString mY;
	int mN;
	int mSizex;
	int mSizey;
	int mFirstSizex;
	int mFirstSizey;
};

}
QML_DECLARE_TYPE(qmlTypes::DeclarativePolygon)
