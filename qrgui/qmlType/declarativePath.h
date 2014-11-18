#pragma once

#include "declarativePen.h"

#include <QtDeclarative/QDeclarativeItem>

namespace qmlTypes {

class DeclarativePath : public DeclarativePen
{
	Q_OBJECT

	Q_PROPERTY(QString str READ str WRITE setStr NOTIFY strChanged)
	Q_PROPERTY(QColor fill READ fill WRITE setFill NOTIFY fillChanged)
	Q_PROPERTY(int sizex READ sizex WRITE setSizex NOTIFY sizexChanged)
	Q_PROPERTY(int sizey READ sizey WRITE setSizey NOTIFY sizeyChanged)

public:
	explicit DeclarativePath(QDeclarativeItem *parent = 0);

	QString str() const;
	QColor fill() const;
	int sizex() const;
	int sizey() const;
	bool isNotLCMZ(QString str, int i);

signals:
	void strChanged();
	void fillChanged();
	void sizexChanged();
	void sizeyChanged();

protected:
	void setStr(QString str);
	void setFill(QColor color);
	void setSizex(int sizex);
	void setSizey(int sizey);
	void updateSize();

private:
	void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget);

protected:
	QString mStr;
	QColor mFill;
	int mSizex;
	int mSizey;
	int mFirstSizex;
	int mFirstSizey;
};

}

QML_DECLARE_TYPE(qmlTypes::DeclarativePath)


