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

	/// Returns path
	QString str() const;
	/// Returns color of path
	QColor fill() const;
	/// Returns width of background
	int sizex() const;
	/// Returns height of background
	int sizey() const;
	///
	bool isNotLCMZ(QString const str, int i);

signals:
	/// Signal change of path
	void strChanged();
	/// Signal change path color
	void fillChanged();
	/// Signal change width of background
	void sizexChanged();
	/// Signal change height of background
	void sizeyChanged();

protected:
	/// Set path
	void setStr(QString str);
	/// Set color of path
	void setFill(QColor color);
	/// Set width of background
	void setSizex(int sizex);
	/// Set height of background
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


