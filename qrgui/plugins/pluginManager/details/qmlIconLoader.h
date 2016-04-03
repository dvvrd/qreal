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

#include <QtCore/QMap>
#include <QtGui/QIcon>

class QQmlEngine;

namespace qReal {

/// Caches qml-described icons.
class QmlIconLoader
{
public:
	/// Configures the only qml icon loader instance to use the given qml engine for rendering icons.
	static void setQmlEngine(QQmlEngine &engine);

	/// Returns a pixmap of element in specified qml-file
	static QIcon iconOf(const QString &qmlString);

	/// Returns a size of the pixmap of element in specified qml-file
	static QSize preferedSizeOf(const QString &qmlString);

private:
	static QmlIconLoader *instance();
	static QIcon loadPixmap(const QString &qmlString);

	QmlIconLoader();
	~QmlIconLoader();

	QQmlEngine *mQmlEngine;
	QMap<QString, QIcon> mLoadedIcons;
	QMap<QString, QSize> mPreferedSizes;
};

}
