#pragma once

#include <QtXml/QDomDocument>
#include <QtWidgets/QGraphicsItem>

#include <qrutils/graphicsUtils/abstractItem.h>

namespace twoDModel {
namespace items {

class ColorFieldItem : public graphicsUtils::AbstractItem
{
public:
	explicit ColorFieldItem(QGraphicsItem* parent = 0);
	virtual ~ColorFieldItem();

	virtual QRectF boundingRect() const = 0;
	virtual void drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) = 0;

	virtual QDomElement serialize(QDomDocument &document, QPoint const &topLeftPicture) = 0;
	virtual void deserialize(QDomElement const &element) = 0;
};

}
}
