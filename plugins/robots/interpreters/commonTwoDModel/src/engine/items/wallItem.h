#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QtGui/QPainter>
#include <QtXml/QDomDocument>

#include "lineItem.h"

namespace twoDModel {
namespace items {

class WallItem : public LineItem
{
	Q_OBJECT

public:
	WallItem(QPointF const &begin, QPointF const &end);

	QPointF begin();
	QPointF end();
	bool isDragged() const;
	qreal width() const;

	/// Draws selection rect around sensorBoundingBox
	void drawExtractionForItem(QPainter *painter) override;
	void drawItem(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) override;

	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

	QDomElement serialize(QDomDocument &document, QPoint const &topLeftPicture) override;
	void deserializePenBrush(QDomElement const &element);

	void onOverlappedWithRobot(bool overlapped = true);

	QPainterPath path() const;

signals:
	void wallDragged(WallItem *item, QPainterPath const &shape, QRectF const &oldPos);

protected:
	void setPrivateData();

private:
	void recalculateBorders();

	bool mDragged;
	bool mOverlappedWithRobot;
	QImage mImage;

	int mOldX1;
	int mOldY1;

	QPainterPath mPath;
};

}
}
