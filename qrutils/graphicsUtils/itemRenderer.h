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

#pragma once

#include <QtWidgets/QGraphicsItem>

#include "qrutils/utilsDeclSpec.h"

namespace graphicsUtils {

/// Provides some utils on rendering QGraphicsItems into QPixmaps and others.
class QRUTILS_EXPORT ItemRenderer
{
public:
	/// Performs graphics item rendering into pixmap of the given size considering all item`s children.
	static QPixmap renderRecursively(QGraphicsItem * const item, int w, int h, const QColor &backgroundColor);

private:
	static void renderItem(QGraphicsItem * const item
			, QPainter *painter
			, QStyleOptionGraphicsItem * const option
			, const QTransform &baseTransform);
};

}
