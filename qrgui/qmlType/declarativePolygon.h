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

	int n() const;
	int sizex() const;
	int sizey() const;
	QColor fill() const;
	QString x() const;
	QString y() const;

signals:
	void fillChanged();
	void xChanged();
	void yChanged();
	void sizexChanged();
	void sizeyChanged();
	void nChanged();

protected:
	void setX(QString x);
	void setY(QString y);
	void setSizex(int sizex);
	void setSizey(int sizey);
	void setFill(QColor color);
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
