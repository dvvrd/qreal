/* Copyright 2014-2016 Dmitry Mordvinov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "itemRenderer.h"

#include <QtGui/QPainter>
#include <QtWidgets/QStyleOptionGraphicsItem>

using namespace graphicsUtils;

QPixmap ItemRenderer::renderRecursively(QGraphicsItem * const item, int w, int h, const QColor &backgroundColor)
{
	// +1 due to strange rendering behaviour
	QPixmap result(w + 1, h + 1);
	QPainter painter(&result);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.save();
	painter.setBrush(backgroundColor);
	painter.setPen(backgroundColor);
	painter.drawRect(0, 0, w + 1, h + 1);
	painter.restore();
	QStyleOptionGraphicsItem option;

	// Get the inverse transform of the root item's scene transform; all the
	// children's transforms will be transformed by this in order to bring
	// their coordinate systems from the scene space to the root item space.
	const QTransform inverse = item->sceneTransform().inverted();

	// Recursively render the item and all its children.
	renderItem(item, &painter, &option, inverse);

	return result;
}

void ItemRenderer::renderItem(QGraphicsItem * const item
		, QPainter *painter
		, QStyleOptionGraphicsItem * const option
		, const QTransform &baseTransform)
{
	const QTransform itemTransform = item->sceneTransform() * baseTransform;
	painter->setWorldTransform(itemTransform, false);
	item->paint(painter, option, nullptr);

	// Recurse into children
	/// @todo this should be breadth-first not depth-first!
	for (QGraphicsItem * const child : item->childItems()) {
		renderItem(child, painter, option, baseTransform);
	}
}
