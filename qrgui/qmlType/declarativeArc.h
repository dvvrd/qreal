#pragma once

#include "declarativePen.h"

#include <QtDeclarative/QDeclarativeItem>

namespace qmlTypes {

/// DeclarativeLineclass is a class that provide qml arc
class DeclarativeArc : public DeclarativePen
{
	Q_OBJECT

	Q_PROPERTY(int x1 READ x1 WRITE setX1 NOTIFY x1Changed)
	Q_PROPERTY(int y1 READ y1 WRITE setY1 NOTIFY y1Changed)
	Q_PROPERTY(int x2 READ x2 WRITE setX2 NOTIFY x2Changed)
	Q_PROPERTY(int y2 READ y2 WRITE setY2 NOTIFY y2Changed)
	Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle NOTIFY startAngleChanged)
	Q_PROPERTY(int spanAngle READ spanAngle WRITE setSpanAngle NOTIFY spanAngleChanged)

public:
	explicit DeclarativeArc(QDeclarativeItem *parent = 0);

	/// Returns the x1 coordinate of the arc
	int x1() const;
	/// Returns the y1 coordinate of the arc
	int y1() const;
	/// Returns the x2 coordinate of the arc
	int x2() const;
	/// Returns the y2 coordinate of the arc
	int y2() const;
	/// Returns the startAngle of the arc
	int startAngle() const;
	/// Return the spanAngle of the arc
	int spanAngle() const;

signals:
	/// Signal change of x1 coordinate
	void x1Changed();
	/// Signal change of y1 coordinate
	void y1Changed();
	/// Signal change of x2 coordinate
	void x2Changed();
	/// Signal change of y2 coordinate
	void y2Changed();
	/// Signal change of startAngle value
	void startAngleChanged();
	/// Signal change of spanAngle value
	void spanAngleChanged();

protected:
	/// Sets the x1 coordinate of the arc
	void setX1(int x1);
	/// Sets the y1 coordinate of the arc
	void setY1(int y1);
	/// Sets the x2 coordinate of the arc
	void setX2(int x2);
	/// Sets the y2 coordinate of the arc
	void setY2(int y2);
	/// Sets the startAngle value
	void setStartAngle(int startAngle);
	/// Sets the spanAngle value
	void setSpanAngle(int spanAngle);
	void updateSize();

private:
	void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget);

protected:
	int mX1;
	int mY1;
	int mX2;
	int mY2;
	int mStartAngle;
	int mSpanAngle;
};

}

QML_DECLARE_TYPE(qmlTypes::DeclarativeArc)

